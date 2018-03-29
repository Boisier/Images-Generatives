#ifndef PathsLinearAlizer_hpp
#define PathsLinearAlizer_hpp

#include "../Instruction.hpp"

class PathsLinearAlizer: public Instruction
{
public:

	static Instruction * get();
	
	std::vector<VectorImage *> execute(std::vector<VectorImage *> &vectorImages);

private:

	PathsLinearAlizer(): Instruction(INSTRUCTION_SOURCE_PATHS, INSTRUCTION_PROPERTY_GEOMETRY, u"linéariser") {};
};

#endif /* PathsLinearAlizer_hpp */
