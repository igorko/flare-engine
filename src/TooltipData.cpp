#include "TooltipData.h"

TooltipData::TooltipData() {
	tip_buffer = NULL;
	default_color = font->getColor("widget_normal");
}

TooltipData::~TooltipData() {
	SDL_FreeSurface(tip_buffer);
}

TooltipData::TooltipData(const TooltipData &tdSource) {

	// DO NOT copy the buffered text render
	// Allow the new copy to create its own buffer
	// Otherwise the same buffer will be deleted twice, causing a mem error
	tip_buffer = NULL;

	lines.clear();
	colors.clear();

	for (unsigned int i=0; i<tdSource.lines.size(); i++) {
		lines.push_back(tdSource.lines[i]);
		colors.push_back(tdSource.colors[i]);
	}
}

TooltipData& TooltipData::operator= (const TooltipData &tdSource) {

	clear();

	for (unsigned int i=0; i<tdSource.lines.size(); i++) {
		lines.push_back(tdSource.lines[i]);
		colors.push_back(tdSource.colors[i]);
	}

	return *this;
}

void TooltipData::clear() {
	lines.clear();
	colors.clear();
	SDL_FreeSurface(tip_buffer);
	tip_buffer = NULL;
}

void TooltipData::addText(const std::string &text, SDL_Color color) {
	lines.push_back("");
	colors.push_back(color);
	for (unsigned int i=0; i<lines.size(); i++) {
		if (lines[i] == "") {
			colors[i] = color;
			for (unsigned int j=0; j<text.length(); j++) {
				if (text[j] == '\n') {
					// insert a space so intentionally blank lines are counted
					if (lines.back() == "") lines.back() += ' ';
					lines.push_back("");
					colors.push_back(color);
				}
				else {
					lines.back() += text[j];
				}
			}
			break;
		}
	}
}

void TooltipData::addText(const std::string &text) {
	addText(text, default_color);
}

bool TooltipData::isEmpty() {
	return lines.empty();
}

bool TooltipData::compareFirstLine(const std::string &text) {
	if (lines.empty()) return false;
	if (lines[0] != text) return false;
	return true;
}

bool TooltipData::compare(const TooltipData *tip) {
	if (lines.size() != tip->lines.size())
		return false;

	for (unsigned int i=0; i<lines.size(); i++) {
		if (lines[i] != tip->lines[i])
			return false;
	}
	return true;
}

