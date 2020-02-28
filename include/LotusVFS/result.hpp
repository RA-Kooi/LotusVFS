#ifndef fb2c7d20_5d6b_5edc_b3a3_b0bf58025db5
#define fb2c7d20_5d6b_5edc_b3a3_b0bf58025db5

#if defined(EASTL_EXCEPTIONS_ENABLED) || defined(VIM_WORKAROUND)
#include <exception>
#endif // EASTL_EXCEPTIONS_ENABLED

#include <EASTL/type_traits.h>

#include <LotusVFS/Details/union_helpers.hpp>

namespace LotusVFS
{
namespace ResultTags
{
struct InPlaceTag{};
inline constexpr InPlaceTag InPlace{};

struct ErrorTag{};
inline constexpr ErrorTag Error{};
} // namespace ResultTags

#if defined(EASTL_EXCEPTIONS_ENABLED) || defined(VIM_WORKAROUND)
namespace Exceptions
{
template<typename E>
class BadResultAccess: public std::exception
{
	static_assert(!eastl::is_same_v<E, void>, "E cannot be void!");

public:
	BadResultAccess() = delete;
	explicit BadResultAccess(E e);
	~BadResultAccess() noexcept override;

	virtual const char *what() const noexcept override;

	inline E const &Error() const &;
	inline E &Error() &;
	inline E const &&Error() const &&;
	inline E &&Error() &&;

private:
	E value;
};

static_assert(std::is_copy_constructible_v<BadResultAccess<int>>);
static_assert(std::is_copy_assignable_v<BadResultAccess<int>>);
static_assert(!std::is_trivially_copyable_v<BadResultAccess<int>>);

static_assert(std::is_move_constructible_v<BadResultAccess<int>>);
static_assert(std::is_move_assignable_v<BadResultAccess<int>>);
} // namespace Exceptions
#endif // EASTL_EXCEPTIONS_ENABLED

template<typename E>
class Error
{
	static_assert(!eastl::is_same_v<E, void>, "E cannot be void!");

public:
	using ValueType = E;

public:
	Error() = delete;
	inline explicit constexpr Error(E const &e);
	inline explicit constexpr Error(E &&e);

	inline constexpr E const &Value() const &;
	inline constexpr E &Value() &;
	inline constexpr E &&Value() &&;
	inline constexpr E &&Value() const &&;

private:
	E value;
};

static_assert(eastl::is_copy_constructible_v<Error<int>>);
static_assert(eastl::is_copy_assignable_v<Error<int>>);
static_assert(eastl::is_trivially_copyable_v<Error<int>>);

static_assert(eastl::is_move_constructible_v<Error<int>>);
static_assert(eastl::is_move_assignable_v<Error<int>>);

template<typename E>
inline constexpr bool operator==(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline constexpr bool operator!=(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline constexpr bool operator<(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline constexpr bool operator<=(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline constexpr bool operator>(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline constexpr bool operator>=(Error<E> const &lhs, Error<E> const &rhs);

template<typename E>
inline Error<eastl::decay<E>> MakeError(E &&e);

template<typename T, typename E>
class Result: private LotusVFS::UnionHelpers::MakeDefaultCtor<T>
{
	using ValueType = T;
	using ErrorType = E;
	using ErrorWrapper = Error<E>;

	template<typename U>
	using Rebind = Result<U, E>;

public:
	constexpr Result() = default;

	inline constexpr Result(T &&value);
	inline constexpr Result(ResultTags::ErrorTag, E &&error);

	Result(Result const &other) = default;
	Result(Result &&other) noexcept = default;
	~Result() noexcept = default;

	Result &operator=(Result const &other) = default;
	Result &operator=(Result &&other) noexcept = default;

private:
	union
	{
		T value;
		E error;
	};

	bool hasValue;
};

static_assert(eastl::is_copy_constructible_v<Result<int, int>>);
static_assert(eastl::is_copy_assignable_v<Result<int, int>>);
static_assert(eastl::is_trivially_copyable_v<Result<int, int>>);

static_assert(eastl::is_move_constructible_v<Result<int, int>>);
static_assert(eastl::is_move_assignable_v<Result<int, int>>);
} // namespace LotusVFS

#endif // fb2c7d20_5d6b_5edc_b3a3_b0bf58025db5
