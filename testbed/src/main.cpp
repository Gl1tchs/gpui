#include <gpui/gpui.h>

int main(const int argc, const char* argv[]) {
	const u32 version = gpui::get_version();
	GPUI_LOG_INFO("GPUI Version: {}.{}.{}", GPUI_GET_MAJOR(version),
			GPUI_GET_MINOR(version), GPUI_GET_PATCH(version));

	gpui::Context context("GPUI Testbed", 800, 600);

	while (context.is_running()) {
		context.update();
	}

	return 0;
}
