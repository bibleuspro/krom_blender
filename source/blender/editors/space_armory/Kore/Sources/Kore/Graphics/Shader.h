#pragma once

#include "Texture.h"
#include "VertexStructure.h"
#include <Kore/Math/Matrix.h>
#include <Kore/ProgramImpl.h>
#include <Kore/ShaderImpl.h>

namespace Kore {
	enum ShaderType { FragmentShader, VertexShader, GeometryShader, TessellationControlShader, TessellationEvaluationShader };

	class Shader : public ShaderImpl {
	public:
		Shader(void* source, int length, ShaderType type);
	};

	class ConstantLocation : public ConstantLocationImpl {};

	class Program : public ProgramImpl {
	public:
		Program();
		void setVertexShader(Shader* shader);
		void setFragmentShader(Shader* shader);
		void setGeometryShader(Shader* shader);
		void setTessellationControlShader(Shader* shader);
		void setTessellationEvaluationShader(Shader* shader);
		void link(VertexStructure& structure) {
			VertexStructure* structures[1] = {&structure};
			link(structures, 1);
		}
		void link(VertexStructure** structures, int count);
		ConstantLocation getConstantLocation(const char* name);
		TextureUnit getTextureUnit(const char* name);
		void set();
	};
}
