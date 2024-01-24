#include "nene/color.h"
#include "nene/core.h"
#include "nene/include/nene/math/rectf.h"
#include "nene/include/nene/math/vec2.h"
#include "nene/math/vec2.h"
#include "nene/math/rectf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct game_Player {
	nene_Vec2 position;
	uint8_t entity_id;
} game_Player;

#define game_Player_SPEED (128.0f)

#define game_PlayerInput_LEFT 1
#define game_PlayerInput_RIGHT 2
#define game_PlayerInput_UP 4
#define game_PlayerInput_DOWN 8

#define game_ROPE_LENGTH 8

typedef struct game_Ball {
	nene_Vec2 position;
	nene_Vec2 velocity;
} game_Ball;

uint8_t game_PlayerInput_get(uint8_t player_id) {
	nene_Scancode left_scancode = NENE_SCANCODE_A;
	nene_Scancode right_scancode = NENE_SCANCODE_D;
	nene_Scancode up_scancode = NENE_SCANCODE_W;
	nene_Scancode down_scancode = NENE_SCANCODE_S;

	if (player_id > 2) {
		printf("WARN: player_id should be either 0 or 1\n");
		return 0;
	}

	if (player_id == 1) {
		left_scancode = NENE_SCANCODE_LEFT;
		right_scancode = NENE_SCANCODE_RIGHT;
		up_scancode = NENE_SCANCODE_UP;
		down_scancode = NENE_SCANCODE_DOWN;
	}

	uint8_t result = 0;

	if (nene_Core_is_scancode_held(left_scancode)) {
		result |= game_PlayerInput_LEFT;
	}
	if (nene_Core_is_scancode_held(right_scancode)) {
		result |= game_PlayerInput_RIGHT;
	}
	if (nene_Core_is_scancode_held(up_scancode)) {
		result |= game_PlayerInput_UP;
	}
	if (nene_Core_is_scancode_held(down_scancode)) {
		result |= game_PlayerInput_DOWN;
	}

	return result;
}

void game_Entity_translate(nene_Vec2 *const position, nene_Vec2 translation) {
	*position = nene_Vec2_add(
		*position,
		nene_Vec2_scale(translation, nene_Core_get_delta_time())
	);
}

nene_Rectf game_Entity_bounding_box(const nene_Vec2 *const position, const nene_Vec2 size) {
	return (nene_Rectf){
		.pos = *position,
		.size = size,
	};
}

void game_Entity_draw(const nene_Rectf bb, nene_Color color) {
	nene_Core_render_draw_rect(
		nene_Rectf_to_rect(bb),
		false,
		color,
		false
	);
	nene_Core_render_draw_rect(
		(nene_Rect){ .pos = nene_Vec2_to_vec2i(bb.pos), .size = {.x = 2, .y = 2 } },
		false,
		nene_Color_white(),
		false
	);
}

game_Player game_Player_init(uint8_t player_id, nene_Vec2 pos) {
	game_Player result = {
		.position = pos,
		.entity_id = player_id,
	};
	return result;
}

void game_Player_update(game_Player *const player) {
	uint8_t player_input = game_PlayerInput_get(player->entity_id);

	if (player_input != 0) {
		nene_Vec2 movement = { .x = 0.0f, .y = 0.0f};

		if ((player_input & game_PlayerInput_LEFT) != 0) {
			movement.x = -game_Player_SPEED;
		}
		else if ((player_input & game_PlayerInput_RIGHT) != 0) {
			movement.x = game_Player_SPEED;
		}
		if ((player_input & game_PlayerInput_UP) != 0) {
			movement.y = -game_Player_SPEED;
		}
		else if ((player_input & game_PlayerInput_DOWN) != 0) {
			movement.y = game_Player_SPEED;
		}

		game_Entity_translate(
			&player->position,
			movement
		);
	}
}

nene_Vec2 game_Player_get_center(const game_Player *const player) {
	return (nene_Vec2){
		.x = player->position.x + 16.0f,
		.y = player->position.y + 16.0f,
	};
}

void game_Player_draw(const game_Player *const player) {
	game_Entity_draw(
		game_Entity_bounding_box(&player->position, (nene_Vec2){ .x = 32, .y = 32 }),
		player->entity_id ? nene_Color_red() : nene_Color_blue()
	);
}

void game_Rope_draw(const nene_Vec2 *const p1, const nene_Vec2 *const p2) {
	const float len = (float)game_ROPE_LENGTH;
	const nene_Vec2i size = { .x = 2, .y = 2};

	for (float i = 0; i < game_ROPE_LENGTH; ++i) {
		nene_Core_render_draw_rect(
			(nene_Rect){
				.pos = nene_Vec2_to_vec2i(nene_Vec2_lerp(*p1, *p2,  i / (len - 1.0f))),
				.size = size
			},
			false,
			nene_Color_cyan(),
			false
		);
	}
}

game_Ball game_Ball_init(nene_Vec2 pos) {
	return (game_Ball){
		.position = pos,
	};
}

void game_Ball_apply_gravity(game_Ball *const ball, float gravity_acc) {
	ball->velocity = nene_Vec2_add(
		ball->velocity,
		nene_Vec2_scale(
			(nene_Vec2){ .y = gravity_acc },
			nene_Core_get_delta_time()
		)
	);
	game_Entity_translate(&ball->position, ball->velocity);
}

bool game_is_segments_intersecting(const nene_Vec2 *const o1, const nene_Vec2 *const e1, const nene_Vec2 *const o2, const nene_Vec2 *const e2) {
	// ported from Nene framework, from nene/src/intersections.c
	// "o" stands for "origin", "e" stands for "ending"
	const nene_Vec2 v1 = nene_Vec2_sub(*e1, *o1);
	const nene_Vec2 v2 = nene_Vec2_sub(*e2, *o2);
	const float cross12 = nene_Vec2_cross(v1, v2);

	if (cross12 == 0.0f) {
		return false;
	}

	const nene_Vec2 oo = nene_Vec2_sub(*o2, *o1);
	const float intersecting_scalar1 = nene_Vec2_cross(oo, v2) / cross12;
	const float intersecting_scalar2 = -nene_Vec2_cross(v1, oo) / cross12;

	return (
		0.0f <= intersecting_scalar1 && intersecting_scalar1 <= 1.0f &&
		0.0f <= intersecting_scalar2 && intersecting_scalar2 <= 1.0f
	);
}

bool game_Ball_is_intersecting_rope(game_Ball *const ball, const nene_Vec2 *const ro, const nene_Vec2 *const re) {
	// ro, re: rope origin, rope ending
	// bbo, bbe: bounding-box origin, bounding-box ending
	nene_Rectf ball_bb = game_Entity_bounding_box(&ball->position, (nene_Vec2){ .x = 16, .y = 16 });
	nene_Vec2 bbo, bbe;

	// top side
	bbo = ball_bb.pos;
	bbe = nene_Vec2_add(bbo, (nene_Vec2){ .x = ball_bb.size.x });
	if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
		return true;
	}
	// right side
	bbo = bbe;
	bbe = nene_Vec2_add(bbe, (nene_Vec2){ .y = ball_bb.size.y });
	if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
		return true;
	}
	// bottom side
	bbo = bbe;
	bbe = nene_Vec2_add(ball_bb.pos, (nene_Vec2){ .y = ball_bb.size.y });
	if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
		return true;
	}
	// left side
	bbo = bbe;
	bbe = ball_bb.pos;
	if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
		return true;
	}

	return false;
}

void game_Ball_update(game_Ball *const ball, const nene_Vec2 *const p1, const nene_Vec2 *const p2) {
	game_Ball_apply_gravity(ball, 48.0f);

	if (game_Ball_is_intersecting_rope(ball, p1, p2)) {
		// TODO: maybe normalize could go after the dot operation...
		nene_Vec2 rope_perp = nene_Vec2_normalize(
			nene_Vec2_perpendicular(
				nene_Vec2_sub(*p2, *p1)
			)
		);

		if (rope_perp.y < 0.0f) {
			rope_perp = nene_Vec2_negate(rope_perp);
		}

		if (nene_Vec2_dot(ball->velocity, rope_perp) > 0.2f) {
			ball->velocity = nene_Vec2_scale(
				nene_Vec2_negate(rope_perp),
				nene_Vec2_len(ball->velocity)
			);
		}
	}
}

void game_Ball_draw(const game_Ball *const ball) {
	game_Entity_draw(
		game_Entity_bounding_box(&ball->position, (nene_Vec2){ .x = 16, .y = 16}),
		nene_Color_yellow()
	);
}

#define game_PLAYER_COUNT 2
game_Player game_players[game_PLAYER_COUNT];
game_Ball game_ball;

int main(int argc, char *argv[]) {
	game_ball = game_Ball_init((nene_Vec2){ .x = 350.0f, .y = 100.0f });
	game_players[0] = game_Player_init(0, (nene_Vec2){ .x = 250.0f, .y = 500.0f });
	game_players[1] = game_Player_init(1, (nene_Vec2){ .x = 450.0f, .y = 500.0f });

	bool ok = nene_Core_init("Make me Laugh Prototype", 800, 600, NENE_WINDOW_FLAG_SHOWN);

	if (!ok) {
		return EXIT_FAILURE;
	}

	do {
		nene_Core_update();

		for (int i = 0; i < game_PLAYER_COUNT; ++i) {
			game_Player_update(&game_players[i]);
		}
		const nene_Vec2 p0_center = game_Player_get_center(&game_players[0]);
		const nene_Vec2 p1_center = game_Player_get_center(&game_players[1]);
		game_Ball_update(&game_ball, &p0_center, &p1_center);

		nene_Core_render_clear(nene_Color_black());

		for (int i = 0; i < game_PLAYER_COUNT; i++) {
			game_Player_draw(&game_players[i]);
		}
		game_Rope_draw(&p0_center, &p1_center);
		game_Ball_draw(&game_ball);

		nene_Core_render_present();
	} while (!nene_Core_should_quit());

	nene_Core_terminate();

	return EXIT_SUCCESS;
}
