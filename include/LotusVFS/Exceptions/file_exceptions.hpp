#ifndef f6eef354_01f4_4d1a_8906_d69eb2d2b818
#define f6eef354_01f4_4d1a_8906_d69eb2d2b818

#include <EASTL/string.h>

#include <LotusCommon/Exceptions/exceptions.hpp>

#include "../api.hpp"

namespace LotusEngine::Exceptions::FileSystems
{
class LOTUSVFS_API FileError: public LotusEngine::Exceptions::RuntimeError
{
public:
	using RuntimeError::RuntimeError;
	FileError(FileError const &) = default;
	~FileError() noexcept override;
};

class LOTUSVFS_API InvalidOpenMode final: public FileError
{
public:
	using FileError::FileError;
	InvalidOpenMode(InvalidOpenMode const &) = default;
	~InvalidOpenMode() noexcept override;
};

class LOTUSVFS_API EndOfFile final: public FileError
{
public:
	using FileError::FileError;
	EndOfFile(EndOfFile const &) = default;
	~EndOfFile() noexcept override;
};

class LOTUSVFS_API IOError final: public FileError
{
public:
	using FileError::FileError;
	IOError(IOError const &) = default;
	~IOError() noexcept override;
};

class LOTUSVFS_API AccessDenied final: public FileError
{
public:
	using FileError::FileError;
	AccessDenied(AccessDenied const &) = default;
	~AccessDenied() noexcept override;
};

class LOTUSVFS_API FileIsDirectory final: public FileError
{
public:
	using FileError::FileError;
	FileIsDirectory(FileIsDirectory const &) = default;
	~FileIsDirectory() noexcept override;
};

class LOTUSVFS_API SymlinkLoop final: public FileError
{
public:
	using FileError::FileError;
	SymlinkLoop(SymlinkLoop const &) = default;
	~SymlinkLoop() noexcept override;
};

class LOTUSVFS_API TooManyFileDescriptors final: public FileError
{
public:
	using FileError::FileError;
	TooManyFileDescriptors(TooManyFileDescriptors const &) = default;
	~TooManyFileDescriptors() noexcept override;
};

class LOTUSVFS_API FileNameTooLong final: public FileError
{
public:
	using FileError::FileError;
	FileNameTooLong(FileNameTooLong const &) = default;
	~FileNameTooLong() noexcept override;
};

class LOTUSVFS_API TooManyOpenFiles final: public FileError
{
public:
	using FileError::FileError;
	TooManyOpenFiles(TooManyOpenFiles const &) = default;
	~TooManyOpenFiles() noexcept override;
};

class LOTUSVFS_API FileNotFound final: public FileError
{
public:
	using FileError::FileError;
	FileNotFound(FileNotFound const &) = default;
	~FileNotFound() noexcept override;
};

class LOTUSVFS_API OutOfSpace final: public FileError
{
public:
	using FileError::FileError;
	OutOfSpace(OutOfSpace const &) = default;
	~OutOfSpace() noexcept override;
};

class LOTUSVFS_API InvalidPath final: public FileError
{
public:
	using FileError::FileError;
	InvalidPath(InvalidPath const &) = default;
	~InvalidPath() noexcept override;
};

class LOTUSVFS_API FileTooBig final: public FileError
{
public:
	using FileError::FileError;
	FileTooBig(FileTooBig const &) = default;
	~FileTooBig() noexcept override;
};

class LOTUSVFS_API FileExists final: public FileError
{
public:
	using FileError::FileError;
	FileExists(FileExists const &) = default;
	~FileExists() noexcept override;
};

class LOTUSVFS_API NotADirectory final: public FileError
{
public:
	using FileError::FileError;
	NotADirectory(NotADirectory const &) = default;
	~NotADirectory() noexcept override;
};
} // namespace LotusEngine::Exceptions::FileSystems

#endif // f6eef354_01f4_4d1a_8906_d69eb2d2b818
