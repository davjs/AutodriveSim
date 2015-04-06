#
# OpenDaVINCI.
#
# This software is open source. Please see COPYING and AUTHORS for further information.
#

PROJECT (libzip)

INCLUDE_DIRECTORIES (${zlib_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES (include)

SET (libziplib-sources
    src/mkstemp.c
    src/zip_add.c
    src/zip_add_dir.c
    src/zip_close.c
    src/zip_delete.c
    src/zip_dirent.c
    src/zip_entry_free.c
    src/zip_entry_new.c
    src/zip_error.c
    src/zip_error_clear.c
    src/zip_error_get.c
    src/zip_error_get_sys_type.c
    src/zip_error_strerror.c
    src/zip_error_to_str.c
    src/zip_err_str.c
    src/zip_fclose.c
    src/zip_file_error_clear.c
    src/zip_file_error_get.c
    src/zip_file_get_offset.c
    src/zip_filerange_crc.c
    src/zip_file_strerror.c
    src/zip_fopen.c
    src/zip_fopen_index.c
    src/zip_fread.c
    src/zip_free.c
    src/zip_get_archive_comment.c
    src/zip_get_archive_flag.c
    src/zip_get_file_comment.c
    src/zip_get_name.c
    src/zip_get_num_files.c
    src/zip_memdup.c
    src/zip_name_locate.c
    src/zip_new.c
    src/zip_open.c
    src/zip_rename.c
    src/zip_replace.c
    src/zip_set_archive_comment.c
    src/zip_set_archive_flag.c
    src/zip_set_file_comment.c
    src/zip_set_name.c
    src/zip_source_buffer.c
    src/zip_source_file.c
    src/zip_source_filep.c
    src/zip_source_free.c
    src/zip_source_function.c
    src/zip_source_zip.c
    src/zip_stat.c
    src/zip_stat_index.c
    src/zip_stat_init.c
    src/zip_strerror.c
    src/zip_unchange_all.c
    src/zip_unchange_archive.c
    src/zip_unchange.c
    src/zip_unchange_data.c    
)

ADD_LIBRARY (ziplib STATIC ${libziplib-sources})
