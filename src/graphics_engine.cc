/*
 * graphics_engine.cc
 *
 *  Created on: Dec 7, 2014
 *      Author: vakz
 */

#include "graphics_engine.h"
#include "window.h"
#include <tuple>
#include <stdexcept>

GraphicsEngine::GraphicsEngine(const std::string window_title,
		const int window_width, const int window_height) :
		window_ { window_title, window_width, window_height }, renderer_ {
				window_ }, viewport_ { 0, 0 } {
	renderer_.set_logical_size(window_.kWidth, window_.kHeight);
	renderer_.set_render_draw_color(0, 0, 0);
	renderer_.clear();
	renderer_.render_present();
}

void GraphicsEngine::redraw_screen(std::vector<Sprite const*> const& sprites){
	std::vector<Sprite const*> visible_sprites;
	get_visible_sprites(sprites, visible_sprites);
	draw_screen(sprites);
}

void GraphicsEngine::draw_screen(std::vector<Sprite const*> const& sprites){
	renderer_.clear();
	for (Sprite const* s : sprites)
	{
		renderer_.render_copy(s->get_texture(), s->get_enclosing_rect(), *s);
	}
	renderer_.render_present();
}

void GraphicsEngine::get_visible_sprites(
		std::vector<Sprite const*> const& sprites,
		std::vector<Sprite const*>& visible) const {

	Rectangle window { viewport_.x, viewport_.y, window_.kWidth, window_.kHeight };
	for (Sprite const* s : sprites) {

		if (s->intersect(window)) {
			visible.push_back(s);
		}
	}
}

bool GraphicsEngine::calc_visible_area(Sprite const* sprite,
		Rectangle& out) const {
	Rectangle window { viewport_.x, viewport_.y, window_.kWidth, window_.kHeight };

	return sprite->intersecting_area(window, out);
}

void GraphicsEngine::set_viewport(Viewport viewport) {

	if (viewport.x < 0 || viewport.y < 0) {
		throw std::invalid_argument("Viewport coordinates must be postivie");
	}
	viewport_ = viewport;
}

Renderer& GraphicsEngine::get_renderer() {
	return renderer_;
}
