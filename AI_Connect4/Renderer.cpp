#include "Renderer.h"
#include "CommandLineRenderer.h"

std::unique_ptr<Renderer> Renderer::MakeRenderer(Type type)
{
	switch (type)
	{
		case Type::COMMAND:
			return std::unique_ptr<Renderer>{new CommandlineRenderer{}};
		default:
			break;
	}
}
