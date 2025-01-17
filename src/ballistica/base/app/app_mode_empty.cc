// Released under the MIT License. See LICENSE for details.

#include "ballistica/base/app/app_mode_empty.h"

#include "ballistica/base/graphics/component/simple_component.h"
#include "ballistica/base/graphics/graphics.h"
#include "ballistica/base/graphics/support/frame_def.h"
#include "ballistica/base/graphics/text/text_group.h"

namespace ballistica::base {

static AppModeEmpty* g_app_mode_empty{};

AppModeEmpty::AppModeEmpty() = default;

auto AppModeEmpty::GetSingleton() -> AppModeEmpty* {
  assert(g_base == nullptr || g_base->InLogicThread());

  if (g_app_mode_empty == nullptr) {
    g_app_mode_empty = new AppModeEmpty();
  }
  return g_app_mode_empty;
}

void AppModeEmpty::Reset() {
  // When we are first created (for use as a placeholder before any app-modes
  // are set) we just draw nothing. However once we actually get reset for use
  // as a an explicit app mode, we do our hello thing.
  hello_mode_ = true;

  // Fade in if we currently aren't.
  g_base->graphics->FadeScreen(true, 250, nullptr);
}

void AppModeEmpty::DrawWorld(base::FrameDef* frame_def) {
  if (!hello_mode_) {
    return;
  }

  // Just draw our spinning hello text.
  if (!hello_text_group_.Exists()) {
    hello_text_group_ = Object::New<TextGroup>();
    hello_text_group_->set_text("Potato!");
  }
  auto& grp(*hello_text_group_);
  auto* pass = frame_def->overlay_pass();
  SimpleComponent c(pass);
  c.SetTransparent(true);
  c.SetColor(0.7f, 0.0f, 1.0f, 1.0f);
  c.PushTransform();

  auto xoffs =
      sinf(static_cast<float>(frame_def->display_time_millisecs()) / 600.0f);
  auto yoffs =
      cosf(static_cast<float>(frame_def->display_time_millisecs()) / 600.0f);
  c.Translate(pass->virtual_width() * 0.5f - 70.0f + xoffs * 200.0f,
              pass->virtual_height() * 0.5f - 20.0f + yoffs * 200.0f);
  c.Scale(2.0, 2.0);

  int text_elem_count = grp.GetElementCount();
  for (int e = 0; e < text_elem_count; e++) {
    c.SetTexture(grp.GetElementTexture(e));
    c.SetFlatness(1.0f);
    c.DrawMesh(grp.GetElementMesh(e));
  }

  c.PopTransform();
  c.Submit();
}

}  // namespace ballistica::base
