#include <cstdlib>
#include <iostream>
#include <vulkan/vulkan.h>

void
printStats(VkPhysicalDevice &device)
{
	VkPhysicalDeviceProperties properties = {};
	VkPhysicalDeviceFeatures features = {};
	VkPhysicalDeviceMemoryProperties memProp = {};
	VkQueueFamilyProperties *familyProperties = nullptr;
	uint32_t width = 0u;
	uint32_t height = 0u;
	uint32_t depth = 0u;
	uint32_t apiVer = 0u;
	uint32_t nQueueFamilies = 0u;
	
	vkGetPhysicalDeviceProperties(device, &properties);
	vkGetPhysicalDeviceFeatures(device, &features);
	vkGetPhysicalDeviceMemoryProperties(device, &memProp);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &nQueueFamilies, nullptr);
	familyProperties = new VkQueueFamilyProperties[nQueueFamilies];
	vkGetPhysicalDeviceQueueFamilyProperties(device, &nQueueFamilies, familyProperties);
	apiVer = properties.apiVersion;
	
	std::cout << "---------------------------------------------------------\n";
	std::cout << "Name:                     " << properties.deviceName << '\n';
	std::cout << "API Version:              " << VK_VERSION_MAJOR(apiVer) << '.' << VK_VERSION_MINOR(apiVer) << '.' << VK_VERSION_PATCH(apiVer) << '\n';
	std::cout << "Driver Version:           " << properties.driverVersion << '\n';
	std::cout << "Vendor ID:                " << properties.vendorID << '\n';
	std::cout << "Device ID:                " << properties.deviceID << '\n';
	std::cout << "Device Type:              " << properties.deviceType << '\n';
	std::cout << "discreteQueuePriorities:  " << properties.limits.discreteQueuePriorities << '\n';
	std::cout << "Geometry Shaders:         " << features.geometryShader << '\n';
	std::cout << "Amount of Queue Families: " << nQueueFamilies << '\n';

	for (auto i = 0; i < nQueueFamilies; ++i) {
		width  = familyProperties[i].minImageTransferGranularity.width;
		height = familyProperties[i].minImageTransferGranularity.height;
		depth  = familyProperties[i].minImageTransferGranularity.depth;
		std::cout << '\n';
		std::cout << "Queue Familiy #" << i << '\n';
		std::cout << "VK_QUEUE_GRAPHICS_BIT:           " << (0 != (familyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) << '\n';
		std::cout << "VK_QUEUE_COMOPUTE_BIT:           " << (0 != (familyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT)) << '\n';
		std::cout << "VK_QUEUE_TRANSFER_BIT:           " << (0 != (familyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT)) << '\n';
		std::cout << "VK_QUEUE_SPARSE_BINDING_BIT:     " << (0 != (familyProperties[i].queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)) << '\n';
		std::cout << "Queue Count:                     " << familyProperties[i].queueCount << '\n';
		std::cout << "Timestamp Valid Bits:            " << familyProperties[i].timestampValidBits << '\n';
		std::cout << "Min Image Timestamp Granularity: " << width << ", " << height << ", " << depth << '\n';
	}
	
	std::cout << "---------------------------------------------------------\n";
	std::cout << std::endl;

	delete[] familyProperties;
	
	return;
}

int
main(void)
{
	VkResult vkErr = VK_SUCCESS;
	uint32_t nPhysicalDevices = 0u;
	VkPhysicalDevice *physicalDevices = nullptr;
	VkLayerProperties *layers = nullptr;
	uint32_t nLayers = 0u;

	VkApplicationInfo appInfo = {
		.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pNext = NULL,
		.pApplicationName = "0661-1920-computer-graphics-project",
		.applicationVersion = VK_MAKE_VERSION(0, 0, 0),
		.pEngineName = "bare-metal",
		.engineVersion = VK_MAKE_VERSION(0, 0, 0),
		.apiVersion = VK_API_VERSION_1_2
	};

	vkErr = vkEnumerateInstanceLayerProperties(&nLayers, nullptr);
	layers = new VkLayerProperties[nLayers];
	vkErr = vkEnumerateInstanceLayerProperties(&nLayers, layers);

	std::cout << "Amount of Instance Layer: " << nLayers << '\n';
	for (auto i = 0; i < nLayers; ++i) {
		std::cout << '\n';
		std::cout << "Name:          " << layers[i].layerName << '\n';
		std::cout << "Spec. Version: " << layers[i].specVersion << '\n';
		std::cout << "Impl. Version: " << layers[i].implementationVersion << '\n';
		std::cout << "Description:   " << layers[i].description << '\n';
	}

	std::cout << std::endl;

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

	physicalDevices = new VkPhysicalDevice[nPhysicalDevices];
	vkErr = vkEnumeratePhysicalDevices(instance, &nPhysicalDevices, physicalDevices);
	if (VK_SUCCESS != vkErr)
		return EXIT_FAILURE;
	for (auto i = 0; i < nPhysicalDevices; ++i)
		printStats(physicalDevices[i]);

	VkDeviceQueueCreateInfo deviceQueueCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueFamilyIndex = 2,
		.queueCount = 4,
		.pQueuePriorities = nullptr
	};

	VkPhysicalDeviceFeatures usedFeatures = {};

	VkDeviceCreateInfo deviceCreateInfo = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.queueCreateInfoCount = 1,
		.pQueueCreateInfos = &deviceQueueCreateInfo,
		.enabledLayerCount = 0,
		.ppEnabledLayerNames = nullptr,
		.enabledExtensionCount = 0,
		.ppEnabledExtensionNames = nullptr,
		.pEnabledFeatures = &usedFeatures
	};

	VkDevice device = {};
	vkErr = vkCreateDevice(physicalDevices[0], &deviceCreateInfo, nullptr, &device);
	if (VK_SUCCESS != vkErr)
		return EXIT_FAILURE;

	delete[] physicalDevices;
	
	return EXIT_SUCCESS;
}
