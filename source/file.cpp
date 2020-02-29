#include "file.hpp"

#include <EASTL/algorithm.h>

#include <cstring>

namespace LotusEngine::FileSystems
{
File::File(LotusEA::PolymorphicAllocator &allocator) noexcept
: allocator(allocator)
, filePath()
, isOpen(false)
, openMode(FileMode::none)
, currentPosition(0)
, size(0)
{
}

tl::expected<eastl::string, File::ReadError> File::ReadCString()
{
	s64 stringLength = 0;
	s64 readPos = currentPosition;

	eastl::vector<byte> data(allocator);

	do
	{
		s64 const readSize = readPos + 128 > size ? size - readPos : size;
		eastl::vector<byte> temp(size_t(readSize), 0, allocator);
		eastl::optional<ReadError> error = PeekData(temp, readSize, readPos);

		if(error)
			return tl::make_unexpected(eastl::move(*error));

		byte const *const end = static_cast<byte const *const>(
			memchr(temp.data(), 0, size_t(readSize)));

		if(end)
			stringLength = readPos
				- currentPosition
				+ intptr_t(end)
				- intptr_t(temp.data());

		readPos += readSize;

		if(readPos == size)
			return tl::make_unexpected(
				Exceptions::FileSystems::EndOfFile(
					filePath.ToString()
					+ ": Trying to read past the end of the file"));

		data.reserve(data.size() + temp.size());
		data.insert(
			data.end(),
			eastl::make_move_iterator(temp.begin()),
			eastl::make_move_iterator(temp.end()));
	} while(!stringLength);

	Skip(stringLength);

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength - 1),
		allocator);

	eastl::copy(
		data.cbegin(),
		eastl::next(data.cbegin(), stringLength),
		output.begin());

	return eastl::move(output);
}

tl::expected<eastl::string, File::ReadError> File::ReadPascalString()
{
	u16 stringLength = 0;
	eastl::optional<ReadError> error = Read(stringLength);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::vector<byte> data(size_t(stringLength), 0, allocator);
	error = ReadData(data, s64(stringLength));

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength),
		allocator);

	eastl::copy(data.cbegin(), data.cend(), output.begin());

	return eastl::move(output);
}
// v ^
tl::expected<eastl::string, File::ReadError> File::ReadPascalCString()
{
	u16 stringLength = 0;
	eastl::optional<ReadError> error = Read(stringLength);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::vector<byte> data(size_t(stringLength), 0, allocator);
	error = ReadData(data, s64(stringLength));

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength),
		allocator);

	eastl::copy(data.cbegin(), eastl::prev(data.cend()), output.begin());

	return eastl::move(output);
}

eastl::string File::ReadCStringEx()
{
	tl::expected<eastl::string, File::ReadError> const error = ReadCString();

	if(!error)
		eastl::visit(
			[](auto &&value){ throw value; },
			eastl::move(error.error()));

	return eastl::move(error.value());
}

tl::expected<eastl::string, File::ReadError> File::PeekCString()
{
	s64 stringLength = 0;
	s64 readPos = currentPosition;

	eastl::vector<byte> data(allocator);

	do
	{
		s64 const readSize = readPos + 128 > size ? size - readPos : size;
		eastl::vector<byte> temp(size_t(readSize), 0, allocator);
		eastl::optional<ReadError> error = PeekData(temp, readSize, readPos);

		if(error)
			return tl::make_unexpected(eastl::move(*error));

		byte const *const end = static_cast<byte const *const>(
			memchr(temp.data(), 0, size_t(readSize)));

		if(end)
			stringLength = readPos
				- currentPosition
				+ intptr_t(end)
				- intptr_t(temp.data());

		readPos += readSize;

		if(readPos == size)
			return tl::make_unexpected(
				Exceptions::FileSystems::EndOfFile(
					filePath.ToString()
					+ ": Trying to read past the end of the file"));

		data.reserve(data.size() + temp.size());
		data.insert(
			data.end(),
			eastl::make_move_iterator(temp.begin()),
			eastl::make_move_iterator(temp.end()));
	} while(!stringLength);

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength - 1),
		allocator);

	eastl::copy(
		data.cbegin(),
		eastl::next(data.cbegin(), stringLength),
		output.begin());

	return eastl::move(output);
}

tl::expected<eastl::string, File::ReadError> File::PeekPascalString()
{
	u16 stringLength = 0;
	eastl::optional<ReadError> error = Peek(stringLength);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::vector<byte> data(size_t(stringLength), 0, allocator);
	error = PeekData(
		data,
		s64(stringLength),
		Position() + s64(sizeof(stringLength)));

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength),
		allocator);

	eastl::copy(data.cbegin(), data.cend(), output.begin());

	return eastl::move(output);
}
// v ^
tl::expected<eastl::string, File::ReadError> File::PeekPascalCString()
{
	u16 stringLength = 0;
	eastl::optional<ReadError> error = Peek(stringLength);

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::vector<byte> data(size_t(stringLength), 0, allocator);
	error = PeekData(
		data,
		s64(stringLength),
		Position() + s64(sizeof(stringLength)));

	if(error)
		return tl::make_unexpected(eastl::move(*error));

	eastl::string output(
		eastl::string::CtorDoNotInitialize{},
		size_t(stringLength),
		allocator);

	eastl::copy(data.cbegin(), eastl::prev(data.cend()), output.begin());

	return eastl::move(output);
}

eastl::string File::PeekCStringEx()
{
	tl::expected<eastl::string, File::ReadError> error = PeekCString();

	if(!error)
		eastl::visit(
			[](auto &&value){ throw value; },
			eastl::move(error.error()));

	return eastl::move(error.value());
}

eastl::optional<File::WriteError> File::WriteCString(eastl::string const &value)
{
	eastl::vector<byte> data(value.size() + 1, 0, allocator);
	eastl::copy(value.cbegin(), value.cend(), data.begin());

	eastl::optional<WriteError> const error = WriteData(data, s64(data.size()));

	return error;
}

eastl::optional<File::WriteError>
File::WritePascalString(eastl::string const &value)
{
	eastl::optional<WriteError> error = Write<u16>(u16(value.size()));

	if(error)
		return error;

	eastl::vector<byte> data(value.size(), 0, allocator);
	eastl::copy(value.cbegin(), value.cend(), data.begin());

	return WriteData(data, s64(data.size()));
}

eastl::optional<File::WriteError>
File::WritePascalCString(eastl::string const &value)
{
	eastl::optional<WriteError> error = Write<u16>(u16(value.size() + 1));

	if(error)
		return error;

	eastl::vector<byte> data(value.size() + 1, 0, allocator);
	eastl::copy(value.cbegin(), value.cend(), data.begin());

	return WriteData(data, s64(data.size()));
}

void File::WriteCStringEx(eastl::string const &value)
{
	eastl::optional<WriteError> const error = WriteCString(value);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));
}

void File::WritePascalStringEx(eastl::string const &value)
{
	eastl::optional<WriteError> const error = WritePascalString(value);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));
}

void File::WritePascalCStringEx(eastl::string const &value)
{
	eastl::optional<WriteError> const error = WritePascalCString(value);

	if(error)
		eastl::visit([](auto &&value){ throw value; }, eastl::move(*error));
}
} // namespace LotusEngine::FileSystems
