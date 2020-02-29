#ifndef c4e7395d_bf56_da76_cf7a_5d5f2a801e9a
#define c4e7395d_bf56_da76_cf7a_5d5f2a801e9a

#include <EASTL/optional.h>
#include <EASTL/type_traits.h>
#include <EASTL/variant.h>

#include <LotusEA/polymorphic_allocator.hpp>
#include <LotusEA/unique_ptr.hpp>

#include <tl/expected.hpp>

#include "Exceptions/file_exceptions.hpp"
#include "api.hpp"
#include "file.hpp"

namespace LotusEngine::FileSystems
{
class Path;

class LOTUSVFS_API FileSystem
{
public:
	using OpenError = eastl::variant
		<
			Exceptions::FileSystems::AccessDenied,
			Exceptions::FileSystems::FileIsDirectory,
			Exceptions::FileSystems::FileNameTooLong,
			Exceptions::FileSystems::FileNotFound,
			Exceptions::FileSystems::FileTooBig,
			Exceptions::FileSystems::InvalidOpenMode,
			Exceptions::FileSystems::InvalidPath,
			Exceptions::FileSystems::SymlinkLoop,
			Exceptions::FileSystems::TooManyFileDescriptors,
			Exceptions::FileSystems::TooManyOpenFiles
		>;

	using CreateError = eastl::variant
		<
			Exceptions::FileSystems::AccessDenied,
			Exceptions::FileSystems::FileExists,
			Exceptions::FileSystems::FileIsDirectory,
			Exceptions::FileSystems::FileNameTooLong,
			Exceptions::FileSystems::IOError,
			Exceptions::FileSystems::InvalidPath,
			Exceptions::FileSystems::OutOfSpace,
			Exceptions::FileSystems::TooManyFileDescriptors,
			Exceptions::FileSystems::TooManyOpenFiles
		>;

	using PopulateError = eastl::variant
		<
			Exceptions::FileSystems::FileNotFound,
			Exceptions::FileSystems::InvalidPath
		>;

	using DirectoryError = eastl::variant
		<
			Exceptions::FileSystems::NotADirectory,
			Exceptions::FileSystems::FileNotFound
		>;

public:
	FileSystem(
		Path const &workingDirectory,
		LotusEA::PolymorphicAllocator &allocator
			= *LotusEA::GetDefaultAllocator());

	FileSystem(FileSystem const &other) = default;
	FileSystem(FileSystem &&other) noexcept = default;
	virtual ~FileSystem() noexcept = default;

	FileSystem &operator=(FileSystem const &other) = delete;
	FileSystem &operator=(FileSystem &&other) noexcept = delete;

	virtual tl::expected<LotusEA::UniquePtr<File>, CreateError>
	CreateFile(Path const &path, bool forceOverwrite = false) = 0;

	inline LotusEA::UniquePtr<File>
	CreateFileEx(Path const &path, bool forceOverwrite = false);

	virtual eastl::optional<CreateError>
	CreateDirectory(Path const &path, bool createChildren = true) = 0;

	virtual tl::expected<LotusEA::UniquePtr<File>, OpenError>
	OpenFile(Path const &path, FileMode openMode) = 0;

	inline LotusEA::UniquePtr<File>
	OpenFileEx(Path const &path, FileMode openMode);

	virtual bool PathExists(Path const &path) const = 0;
	virtual eastl::optional<PopulateError>
	PopulatePathInfo(Path &path, bool allNodes = false) = 0;

	virtual tl::expected<eastl::vector<Path>, DirectoryError>
	DirectoryChildren(Path const &path);

	inline eastl::vector<Path> DirectoryChildrenEx(Path const &path);

	inline Path const &CurrentWorkingDirectory() const noexcept;
	inline void ChangeCurrentWorkingDirectory(Path const &newWorkingDirectory);

protected:
	LotusEA::PolymorphicAllocator &allocator;
	Path currentWorkingDirectory;
};

static_assert(!eastl::is_copy_constructible_v<FileSystem>);
static_assert(!eastl::is_copy_assignable_v<FileSystem>);
static_assert(!eastl::is_trivially_copyable_v<FileSystem>);

static_assert(!eastl::is_move_constructible_v<FileSystem>);
static_assert(!eastl::is_move_assignable_v<FileSystem>);
} // namespace LotusEngine::FileSystems

#ifndef VIM_WORKAROUND
#include "file_system_impl.hpp"
#endif

#endif // c4e7395d_bf56_da76_cf7a_5d5f2a801e9a
