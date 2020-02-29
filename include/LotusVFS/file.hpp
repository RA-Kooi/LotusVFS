#ifndef c751ea6f_3fa0_4196_8939_4579e667015a
#define c751ea6f_3fa0_4196_8939_4579e667015a

#include <EASTL/optional.h>
#include <EASTL/string.h>
#include <EASTL/type_traits.h>
#include <EASTL/unique_ptr.h>
#include <EASTL/variant.h>
#include <EASTL/vector.h>

#include <LotusCommon/types.hpp>

#include <LotusEA/polymorphic_allocator.hpp>

#include <tl/expected.hpp>

#include "Exceptions/file_exceptions.hpp"
#include "api.hpp"
#include "path.hpp"

namespace LotusEngine::FileSystems
{
using namespace LotusEngine::Types;

namespace FileOpenMode
{
enum value
{
	none   = 0,
	read   = 1 << 0,
	write  = 1 << 1,
	shared = 1 << 2
};
} // FileOpenMode

using FileMode = FileOpenMode::value;

class LOTUSVFS_API File
{
public:
	using ReadError = eastl::variant
		<
			Exceptions::FileSystems::EndOfFile,
			Exceptions::FileSystems::IOError
		>;

	using WriteError = eastl::variant
		<
			Exceptions::FileSystems::IOError,
			Exceptions::FileSystems::OutOfSpace
		>;

	enum class SeekMode: u8
	{
		begin,
		current,
		end
	};

public:
	File(
		LotusEA::PolymorphicAllocator &allocator
			= *LotusEA::GetDefaultAllocator()) noexcept;

	File(File const &other) = delete;
	File(File &&other) noexcept;
	virtual ~File() noexcept;

	File &operator=(File const &other) = delete;
	File &operator=(File &&other) noexcept;

	inline class Path const &Path() const noexcept;
	inline FileMode OpenMode() const noexcept;

	inline s64 Position() const noexcept;
	inline s64 Size() const noexcept;

	virtual void Open(class Path const &filePath, FileMode openMode) = 0;
	virtual void Close() noexcept = 0;

	virtual void Seek(s64 offset, SeekMode seekMode = SeekMode::begin) = 0;
	inline void Skip(s64 bytes);

	template<typename T>
	inline T ReadEx();

	template<typename T>
	inline void ReadEx(T &value);

	template<typename T>
	inline tl::expected<T, ReadError> Read();

	template<typename T>
	inline eastl::optional<ReadError> Read(T &value);

	tl::expected<eastl::string, ReadError> ReadCString();
	tl::expected<eastl::string, ReadError> ReadPascalString();
	tl::expected<eastl::string, ReadError> ReadPascalCString();

	eastl::string ReadCStringEx();
	eastl::string ReadPascalStringEx();
	eastl::string ReadPascalCStringEx();

	virtual eastl::optional<ReadError>
	ReadData(eastl::vector<byte> &dest, s64 length) = 0;

	template<typename T>
	inline T PeekEx();

	template<typename T>
	inline void PeekEx(T &value);

	template<typename T>
	inline tl::expected<T, ReadError> Peek();

	template<typename T>
	inline eastl::optional<ReadError> Peek(T &value);

	tl::expected<eastl::string, ReadError> PeekCString();
	tl::expected<eastl::string, ReadError> PeekPascalString();
	tl::expected<eastl::string, ReadError> PeekPascalCString();

	eastl::string PeekCStringEx();
	eastl::string PeekPascalStringEx();
	eastl::string PeekPascalCStringEx();

	virtual eastl::optional<ReadError>
	PeekData(eastl::vector<byte> &dest, s64 length, s64 position) = 0;

	template<typename T>
	inline eastl::optional<WriteError> Write(T const &value);

	template<typename T>
	inline void WriteEx(T const &value);

	eastl::optional<WriteError> WriteCString(eastl::string const &value);
	eastl::optional<WriteError> WritePascalString(eastl::string const &value);
	eastl::optional<WriteError> WritePascalCString(eastl::string const &value);

	void WriteCStringEx(eastl::string const &value);
	void WritePascalStringEx(eastl::string const &value);
	void WritePascalCStringEx(eastl::string const &value);

	virtual eastl::optional<WriteError>
	WriteData(eastl::vector<byte> const &source, s64 length) = 0;

protected:
	LotusEA::PolymorphicAllocator &allocator;
	class Path filePath;
	bool isOpen;
	FileMode openMode;
	s64 currentPosition;
	s64 size;
};

static_assert(!eastl::is_copy_constructible_v<File>);
static_assert(!eastl::is_copy_assignable_v<File>);
static_assert(!eastl::is_trivially_copyable_v<File>);

static_assert(!eastl::is_move_constructible_v<File>);
static_assert(eastl::is_move_assignable_v<File>);

inline eastl::string OpenModeToString(FileMode openMode);
} // namespace LotusEngine::FileSystems

#ifndef VIM_WORKAROUND
#include "file_impl.hpp"
#endif

#endif // c751ea6f_3fa0_4196_8939_4579e667015a
