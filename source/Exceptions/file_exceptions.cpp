#include "Exceptions/file_exceptions.hpp"

namespace LotusEngine::Exceptions::FileSystems
{
FileError::~FileError() noexcept = default;

InvalidOpenMode::~InvalidOpenMode() noexcept = default;

EndOfFile::~EndOfFile() noexcept = default;

IOError::~IOError() noexcept = default;

AccessDenied::~AccessDenied() noexcept = default;

FileIsDirectory::~FileIsDirectory() noexcept = default;

SymlinkLoop::~SymlinkLoop() noexcept = default;

TooManyFileDescriptors::~TooManyFileDescriptors() noexcept = default;

FileNameTooLong::~FileNameTooLong() noexcept = default;

TooManyOpenFiles::~TooManyOpenFiles() noexcept = default;

FileNotFound::~FileNotFound() noexcept = default;

OutOfSpace::~OutOfSpace() noexcept = default;

InvalidPath::~InvalidPath() noexcept = default;

FileTooBig::~FileTooBig() noexcept = default;

FileExists::~FileExists() noexcept = default;

NotADirectory::~NotADirectory() noexcept = default;
} // namespace LotusEngine::Exceptions::FileSystems
