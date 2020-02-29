#ifndef e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24
#define e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24

#include <EASTL/type_traits.h>
#include <EASTL/string.h>
#include <EASTL/vector.h>

namespace LotusEngine::FileSystems
{
class PathNode final
{
public:
	PathNode(eastl::string const &name);

	PathNode(PathNode const &other) = default;
	PathNode(PathNode &&other) noexcept = default;
	~PathNode() noexcept = default;

	PathNode &operator=(PathNode const &other) = default;
	PathNode &operator=(PathNode &&other) noexcept = default;

private:
	eastl::string name;
	bool isDirectory, isSymlink, populatedInfo;
};

static_assert(std::is_copy_constructible_v<PathNode>);
static_assert(std::is_copy_assignable_v<PathNode>);
static_assert(!std::is_trivially_copyable_v<PathNode>);

static_assert(std::is_move_constructible_v<PathNode>);
static_assert(std::is_move_assignable_v<PathNode>);

class Path final
{
public:
	Path() = default;

	Path(eastl::string const &path);

	Path(Path const &other) = default;
	Path(Path &&other) noexcept = default;
	~Path() noexcept = default;

	Path &operator=(Path const &other) = default;
	Path &operator=(Path &&other) noexcept = default;

	eastl::string ToString();

private:
	eastl::vector<PathNode> nodes;
};

static_assert(eastl::is_copy_constructible_v<Path>);
static_assert(eastl::is_copy_assignable_v<Path>);
static_assert(!eastl::is_trivially_copyable_v<Path>);

static_assert(eastl::is_move_constructible_v<Path>);
static_assert(eastl::is_move_assignable_v<Path>);
} // namespace LotusVFS

#endif // e8f9742d_6cfe_e70d_3f2d_1ae6de5a2b24
