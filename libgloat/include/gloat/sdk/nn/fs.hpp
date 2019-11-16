#pragma once

#include <cstddef>

#include "Result.hpp"

namespace nn {
namespace fs {
struct FileHandle {
    void* handle;  // probably??? It doesn't seems to use more than 8 bytes
};

struct DirectoryHandle {
    void* handle;  // probably???
};

struct WriteOption {
    int mode;  // mode is unknown (maybe something related to flush?)
};

enum FileOpenMode {
    FileOpenMode_Readable = 1 << 0,
    FileOpenMode_Writable = 1 << 1,
    FileOpenMode_Appendable = 1 << 2,
};

enum DirectoryOpenMode {
    DirectoryOpenMode_Directories = 1 << 0,
    DirectoryOpenMode_Files = 1 << 1,
    DirectoryOpenMode_All =
        DirectoryOpenMode_Directories | DirectoryOpenMode_Files,
};

nn::Result MountSdCard(char const* mountPoint);
nn::Result MountSdCardForDebug(char const* mountPoint);

nn::Result CreateFile(char const* path, long size);
nn::Result OpenFile(FileHandle* handle, char const* path, int mode);
nn::Result FlushFile(FileHandle handle);

nn::Result SetFileSize(FileHandle handle, long size);
nn::Result GetFileSize(long* fileSize, FileHandle handle);

nn::Result ReadFile(FileHandle handle, long offset, void* buffer,
                    unsigned long buffer_size);
nn::Result WriteFile(FileHandle handle, long offset, void const* buffer,
                     unsigned long buffer_size, WriteOption const& option);
void CloseFile(FileHandle handle);

nn::Result OpenDirectory(DirectoryHandle* handle, char const* path, int mode);

nn::Result CloseDirectory(DirectoryHandle handle);

void SetAllocator(void* allocator(size_t), void deallocator(void*, size_t));

void SetEnabledAutoAbort(bool autoAbort);
}  // namespace fs
}  // namespace nn