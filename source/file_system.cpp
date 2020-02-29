#include "file_system.hpp"

namespace LotusEngine::FileSystems
{
FileSystem::FileSystem(
	Path const &workingDirectory,
	LotusEA::PolymorphicAllocator &allocator)
: allocator(allocator)
, currentWorkingDirectory(workingDirectory)
{
}
} // namespace LotusEngine::FileSystems
