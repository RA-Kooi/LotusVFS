#ifndef e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24
#define e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24

#include <EASTL/optional.h>
#include <EASTL/type_traits.h>
#include <EASTL/string.h>
#include <EASTL/variant.h>
#include <EASTL/vector.h>

#include <LotusCommon/types.hpp>

namespace LotusEngine::FileSystems
{
using namespace LotusEngine::Types;

namespace PathFlagsNS
{
enum value
{
	invalid   = 0,
	file      = 1 << 0,
	directory = 1 << 1,
	symlink   = 1 << 2
};
} // namespace PathFlagsNS

using PathFlags = PathFlagsNS::value;

class PathNode final
{
public:
	PathNode(eastl::string const &name);

	PathNode(PathNode const &other) = default;
	PathNode(PathNode &&other) noexcept = default;
	~PathNode() noexcept = default;

	PathNode &operator=(PathNode const &other) = default;
	PathNode &operator=(PathNode &&other) noexcept = default;

	eastl::string const &Name() const noexcept;

private:
	eastl::string name;
};

static_assert(eastl::is_copy_constructible_v<PathNode>);
static_assert(eastl::is_copy_assignable_v<PathNode>);
static_assert(!eastl::is_trivially_copyable_v<PathNode>);

static_assert(eastl::is_move_constructible_v<PathNode>);
static_assert(eastl::is_move_assignable_v<PathNode>);

class Path final
{
public:
	Path() = default;

	Path(eastl::string const &path);
	Path(eastl::vector<PathNode> const &nodes);
	Path(PathNode const &rootNode);

	Path(Path const &other) = default;
	Path(Path &&other) noexcept = default;
	~Path() noexcept = default;

	Path &operator=(Path const &other) = default;
	Path &operator=(Path &&other) noexcept = default;

	Path &operator+=(Path const &other);
	Path &operator/=(Path const &other);
	Path &operator-=(Path const &other);
	Path &operator-=(size_t levels);

	eastl::string ToString() const;
	eastl::string ToWindowsString() const;
	eastl::string ToUnixString() const;

	bool Relative() const;

	eastl::optional<Path> CommonPrefix(Path const &other) const;

	eastl::optional<Path> Relative(Path const &other) const;

	Path RelativeMismatch(Path const &other) const;

	eastl::optional<Path> Absolute(eastl::optional<Path> root) const;

	eastl::string FileName() const;
	eastl::string Extension() const;
	eastl::string FullName() const;

	// Path without file extension
	Path FilePath() const;

private:
	eastl::vector<PathNode> nodes;
};

static_assert(eastl::is_copy_constructible_v<Path>);
static_assert(eastl::is_copy_assignable_v<Path>);
static_assert(!eastl::is_trivially_copyable_v<Path>);

static_assert(eastl::is_move_constructible_v<Path>);
static_assert(eastl::is_move_assignable_v<Path>);

class PathInfo final
{
public:
	PathInfo(Path const &basePath);
	PathInfo(PathInfo const &other) = default;
	PathInfo(PathInfo &&other) noexcept = default;
	~PathInfo() noexcept;

	PathInfo &operator=(PathInfo const &other) = delete;
	PathInfo &operator=(PathInfo &&other) noexcept = delete;

	bool Directory() const noexcept;
	bool File() const noexcept;
	bool Symlink() const noexcept;

	s64 ChildCount() const;
	s64 FileSize() const;

	eastl::vector<PathNode> const &Children() const;
	Path const &Target() const;

	Path const &BasePath() const;

private:
	Path const &base;
	PathFlags flags;

	eastl::variant
	<
		s64 /*fileSize*/,
		eastl::vector<PathNode> /*children*/,
		Path /*target*/
	> info;
};

static_assert(eastl::is_copy_constructible_v<PathInfo>);
static_assert(!eastl::is_copy_assignable_v<PathInfo>);
static_assert(!eastl::is_trivially_copyable_v<PathInfo>);

static_assert(eastl::is_move_constructible_v<PathInfo>);
static_assert(!eastl::is_move_assignable_v<PathInfo>);
} // namespace LotusVFS

#endif // e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24
