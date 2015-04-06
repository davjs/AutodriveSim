#ifndef __CXXTEST__EXECUTIONLOG_H
#define __CXXTEST__EXECUTIONLOG_H

#include <vector>
#include <string>

#define LOG_TEST_SUCCESS        ((signed char)0)
#define LOG_TEST_FAILED_ASSERT  ((signed char)-1)
#define LOG_TEST_FAILED_TEST    ((signed char)-2)
// positive values indicate signal number of error tests

class TestResultInfo
{
public:
	signed char code;
	std::string message;
	
	TestResultInfo(signed char c, std::string m = std::string()) :
		code(c), message(m) { }
};

class ExecutionLog
{
private:
	std::vector<TestResultInfo> testResults;
	size_t failureCount; 
	TestResultInfo lastResult;

public:
	ExecutionLog() : failureCount(0), lastResult(LOG_TEST_SUCCESS)
	{
	}
	
	void setLastResult(signed char code, std::string msg = std::string())
	{
		lastResult = TestResultInfo(code, msg);
	}
	
	void commitLastResult()
	{
		if(lastResult.code != LOG_TEST_SUCCESS)
			failureCount++;

		testResults.push_back(lastResult);
		lastResult = TestResultInfo(LOG_TEST_SUCCESS);
	}

	bool isLastResultSet() const
	{
		return (lastResult.code != LOG_TEST_SUCCESS);
	}

	size_t getTestCount() const
	{
		return testResults.size();
	}
	
	size_t getFailureCount() const
	{
		return failureCount;
	}

	void write32(FILE* file, unsigned int val)
	{
		fputc(val & 0xFF, file);
		fputc((val >> 8) & 0xFF, file);
		fputc((val >> 16) & 0xFF, file);
		fputc((val >> 24) & 0xFF, file);
	}
	
	unsigned int read32(FILE* file)
	{
		int bytes[4];
		bytes[0] = fgetc(file);
		bytes[1] = fgetc(file);
		bytes[2] = fgetc(file);
		bytes[3] = fgetc(file);

		return bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
	}

	void appendToFile(const char* path)
	{
		FILE* logFile = fopen(path, "r+b");
		if(logFile == NULL)
			logFile = fopen(path, "w+b");

		fseek(logFile, 0, SEEK_END);
		int tailPos = ftell(logFile);
		
		if(tailPos == 0)
		{
			// Log file is empty.  Write the header first.
			tailPos = 4;			
			write32(logFile, tailPos);
		}
		else
		{
			// Update next pointer of last record.
			fseek(logFile, 0, SEEK_SET);
			int lastPos = read32(logFile);
			fseek(logFile, lastPos, SEEK_SET);
			write32(logFile, tailPos);

			// Update tail pointer.
			fseek(logFile, 0, SEEK_SET);
			write32(logFile, tailPos);
		}
		
		fseek(logFile, tailPos, SEEK_SET);

		size_t testCount = getTestCount();
		write32(logFile, (unsigned int)-1);	// next ptr
		write32(logFile, testCount);
		write32(logFile, failureCount);

		time_t currentTime = time(NULL);
		write32(logFile, currentTime);

		for(size_t i = 0; i < testCount; i++)
		{
			const TestResultInfo& info = testResults[i];
			fputc(info.code, logFile);
			
			for(size_t j = 0; j < info.message.length(); j++)
				fputc(info.message[j] ^ 0x80, logFile);
			
			fputc('\0' ^ 0x80, logFile);
		}

		fclose(logFile);
	}
};

// This will be defined in the generated runAllTests.cpp.
extern ExecutionLog executionLog;

#endif // __CXXTEST__EXECUTIONLOG_H
