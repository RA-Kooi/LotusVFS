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
	~FileError() noexcept override;
};

class LOTUSVFS_API InvalidOpenMode final: public FileError
{
public:
	using FileError::FileError;
	~InvalidOpenMode() noexcept override;
};

class LOTUSVFS_API EndOfFile final: public FileError
{
public:
	using FileError::FileError;
	~EndOfFile() noexcept override;
};

class LOTUSVFS_API IOError final: public FileError
{
public:
	using FileError::FileError;
	~IOError() noexcept override;
};

class LOTUSVFS_API AccessDenied final: public FileError
{
public:
	using FileError::FileError;
	~AccessDenied() noexcept override;
};

class LOTUSVFS_API FileIsDirectory final: public FileError
{
public:
	using FileError::FileError;
	~FileIsDirectory() noexcept override;
};

class LOTUSVFS_API SymlinkLoop final: public FileError
{
public:
	using FileError::FileError;
	~SymlinkLoop() noexcept override;
};

class LOTUSVFS_API TooManyFileDescriptors final: public FileError
{
public:
	using FileError::FileError;
	~TooManyFileDescriptors() noexcept override;
};

class LOTUSVFS_API FileNameTooLong final: public FileError
{
public:
	using FileError::FileError;
	~FileNameTooLong() noexcept override;
};

class LOTUSVFS_API TooManyOpenFiles final: public FileError
{
public:
	using FileError::FileError;
	~TooManyOpenFiles() noexcept override;
};

class LOTUSVFS_API FileNotFound final: public FileError
{
public:
	using FileError::FileError;
	~FileNotFound() noexcept override;
};

class LOTUSVFS_API OutOfSpace final: public FileError
{
public:
	using FileError::FileError;
	~OutOfSpace() noexcept override;
};

class LOTUSVFS_API InvalidPath final: public FileError
{
public:
	using FileError::FileError;
	~InvalidPath() noexcept override;
};

class LOTUSVFS_API FileTooBig final: public FileError
{
public:
	using FileError::FileError;
	~FileTooBig() noexcept override;
};

class LOTUSVFS_API FileExists final: public FileError
{
public:
	using FileError::FileError;
	~FileExists() noexcept override;
};

class LOTUSVFS_API NotADirectory final: public FileError
{
public:
	using FileError::FileError;
	~NotADirectory() noexcept override;
};
} // namespace LotusEngine::Exceptions::FileSystems

#endif // f6eef354_01f4_4d1a_8906_d69eb2d2b818
