#include <cstdlib>

#include <vulkan/vulkan.h>

int
main(void)
{
	VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = "0661-1920-computer-graphics-project",
		.applicationVersion = VK_MAKE_VERSION(0, 0, 0),
		.pEngineName = "bare-metal",
		.engineVersion = VK_MAKE_VERSION(0, 0, 0),
		.apiVersion = VK_API_VERSION_1_1
	};
	
	return EXIT_SUCCESS;
}
