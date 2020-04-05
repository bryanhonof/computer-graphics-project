#include <cstdlib>
#include <iostream>
#include <vulkan/vulkan.h>

int
main(void)
{
	VkResult vkErr = VK_SUCCESS;
	uint32_t nPhysicalDevices = 0u;
	
	VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = "0661-1920-computer-graphics-project",
		.applicationVersion = VK_MAKE_VERSION(0, 0, 0),
		.pEngineName = "bare-metal",
		.engineVersion = VK_MAKE_VERSION(0, 0, 0),
		.apiVersion = VK_API_VERSION_1_2
	};

	VkInstanceCreateInfo instanceInfo = {
		.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.pApplicationInfo = &appInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = nullptr
	};

	VkInstance instance = {};
	
	vkErr = vkCreateInstance(&instanceInfo, nullptr, &instance);	
	if (VK_SUCCESS != vkErr)
		return EXIT_FAILURE;

	vkErr = vkEnumeratePhysicalDevices(instance, &nPhysicalDevices, nullptr);
	if (VK_SUCCESS != vkErr)
		return EXIT_FAILURE;

	VkPhysicalDevice *physicalDevices = new VkPhysicalDevice[nPhysicalDevices];
	vkErr = vkEnumeratePhysicalDevices(instance, &nPhysicalDevices, physicalDevices);
	if (VK_SUCCESS != vkErr)
		return EXIT_FAILURE;
	
	return EXIT_SUCCESS;
}
