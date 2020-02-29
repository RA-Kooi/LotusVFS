#ifndef f24f2fcd_08d9_40e8_bc63_2f333e403387
#define f24f2fcd_08d9_40e8_bc63_2f333e403387

#ifdef VIM_WORKAROUND
#include "file_system.hpp"
#endif

namespace LotusEngine::FileSystems
{
inline LotusEA::UniquePtr<File>
FileSystem::CreateFileEx(Path const &path, bool forceOverwrite)
{
	tl::expected<LotusEA::UniquePtr<File>, CreateError> error =
		CreateFile(path, forceOverwrite);

	if(!error)
		eastl::visit(
			[](auto &&value){ throw value; },
			eastl::move(error.error()));

	return eastl::move(error.value());
}

inline LotusEA::UniquePtr<File>
FileSystem::OpenFileEx(Path const &path, FileMode openMode)
{
	tl::expected<LotusEA::UniquePtr<File>, OpenError> error =
		OpenFile(path, openMode);

	if(!error)
		eastl::visit(
			[](auto &&value){ throw value; },
			eastl::move(error.error()));

	return eastl::move(error.value());
}

inline eastl::vector<Path> FileSystem::DirectoryChildrenEx(Path const &path)
{
	tl::expected<eastl::vector<Path>, DirectoryError> error =
		DirectoryChildren(path);

	if(!error)
		eastl::visit(
			[](auto &&value){ throw value; },
			eastl::move(error.error()));

	return eastl::move(error.value());
}

inline Path const &FileSystem::CurrentWorkingDirectory() const noexcept
{
	return currentWorkingDirectory;
}

inline void FileSystem::ChangeCurrentWorkingDirectory(
	Path const &newWorkingDirectory)
{
	currentWorkingDirectory = newWorkingDirectory;
}
} // namespace LotusEngine::FileSystems

#endif // f24f2fcd_08d9_40e8_bc63_2f333e403387
