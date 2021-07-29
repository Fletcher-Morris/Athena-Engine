#include "Athena.h"

class Forge : public Athena::App
{
public:
	Forge()
	{
	}
};

Athena::App* Athena::CreateApp()
{
	return new Forge();
}