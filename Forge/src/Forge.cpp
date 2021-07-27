#include <Athena.h>

class Forge : public Athena::App
{

};

Athena::App* Athena::CreateApp()
{
	return new Forge();
}