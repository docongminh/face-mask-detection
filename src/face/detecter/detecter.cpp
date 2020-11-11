#include "anticonv/anticonv.h"

namespace mirror {
Detecter* AnticonvFactory::CreateDetecter()
{
	return new AntiConv();
}

}
