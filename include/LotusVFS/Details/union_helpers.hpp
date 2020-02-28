#ifndef c262831d_c278_a425_cbe1_c8c84fb4035a
#define c262831d_c278_a425_cbe1_c8c84fb4035a

#include <EASTL/type_traits.h>

namespace LotusVFS::UnionHelpers
{
struct DefaultConstructorTag
{
	explicit constexpr DefaultConstructorTag() = default;
};

template<typename T, bool = eastl::is_default_constructible_v<T>>
struct MakeDefaultCtor
{
	MakeDefaultCtor() = default;

	MakeDefaultCtor(DefaultConstructorTag) {}
};

template<typename T>
struct MakeDefaultCtor<T, false>
{
	MakeDefaultCtor() = delete;

	MakeDefaultCtor(DefaultConstructorTag) {}
};

static_assert(eastl::is_copy_constructible_v<MakeDefaultCtor<int>>);
static_assert(eastl::is_copy_assignable_v<MakeDefaultCtor<int>>);
static_assert(eastl::is_trivially_copyable_v<MakeDefaultCtor<int>>);

static_assert(eastl::is_move_constructible_v<MakeDefaultCtor<int>>);
static_assert(eastl::is_move_assignable_v<MakeDefaultCtor<int>>);
} // namespace LotusVFS::UnionHelpers

#endif // c262831d_c278_a425_cbe1_c8c84fb4035a
