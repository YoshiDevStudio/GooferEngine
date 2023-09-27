#pragma once

#ifdef GOOF_PLATFORM_WINDOWS

extern Goofer::Application* Goofer::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Goofer::CreateApplication();
	app->Run();

	delete app;
}

#endif
