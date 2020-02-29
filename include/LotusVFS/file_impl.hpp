#ifndef a415ce22_9bde_44d9_b9db_c7064e93b1ec
#define a415ce22_9bde_44d9_b9db_c7064e93b1ec

#ifdef VIM_WORKAROUND
#include "file.hpp"
#endif

#include <EASTL/algorithm.h>

namespace LotusEngine::FileSystems
{
inline class Path const &File::Path() const noexcept
{
	return filePath;
}

inline FileMode File::OpenMode() const noexcept
{
	return openMode;
}

inline s64 File::Position() const noexcept
{
	return currentPosition;
}

inline s64 File::Size() const noexcept
{
	return size;
}

inline void File::Skip(s64 bytes)
{
	Seek(bytes, SeekMode::current);
}

template<typename T>
inline T File::ReadEx()
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	T ret;
	eastl::optional<ReadError> const error = Read(ret);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));

	return ret;
}

template<typename T>
inline void File::ReadEx(T &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::vector<byte> temp(sizeof(T), 0, allocator);
	eastl::optional<ReadError> const error = ReadData(temp, sizeof(T));

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));

	value = *reinterpret_cast<T>(&temp[0]);
}

template<typename T>
tl::expected<T, File::ReadError> File::Read()
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	T ret;
	eastl::optional<ReadError> const error = Read(ret);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	return ret;
}

template<typename T>
eastl::optional<File::ReadError> File::Read(T &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::vector<byte> temp(sizeof(T), 0, allocator);
	eastl::optional<ReadError> const error = ReadData(temp, sizeof(T));

	value = *reinterpret_cast<T*>(&temp[0]);

	return error;
}

template<typename T>
inline T File::PeekEx()
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	T ret;
	eastl::optional<ReadError> const error = Peek(ret);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));

	return ret;
}

template<typename T>
inline void File::PeekEx(T &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::vector<byte> temp(sizeof(T), 0, allocator);
	eastl::optional<ReadError> const error = PeekData(
		temp,
		sizeof(T),
		Position());

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));

	value = *reinterpret_cast<T>(&temp[0]);
}

template<typename T>
tl::expected<T, File::ReadError> File::Peek()
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	T ret;
	eastl::optional<ReadError> const error = Peek(ret);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	return ret;
}

template<typename T>
eastl::optional<File::ReadError> File::Peek(T &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::vector<byte> temp(sizeof(T), 0, allocator);
	eastl::optional<ReadError> const error =
		PeekData(temp, sizeof(T), Position());

	value = *reinterpret_cast<T*>(&temp[0]);

	return error;
}

template<typename T>
inline eastl::optional<File::WriteError> File::Write(T const &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::vector<byte> temp(sizeof(T), 0, allocator);
	byte const *const valueBytes = reinterpret_cast<byte const *const>(&value);
	eastl::copy(valueBytes, valueBytes + sizeof(T), temp.begin());

	return WriteData(temp, sizeof(T));
}

template<typename T>
inline void File::WriteEx(T const &value)
{
	static_assert(eastl::is_fundamental_v<T>, "T must be a primite type.");

	eastl::optional<WriteError> const error = Write(value);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));
}
} // namespace LotusEngine::FileSystems

#endif // a415ce22_9bde_44d9_b9db_c7064e93b1ec
