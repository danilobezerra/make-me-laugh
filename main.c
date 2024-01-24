#include "nene/color.h"
#include "nene/core.h"
#include "nene/include/nene/math/rectf.h"
#include "nene/include/nene/math/vec2.h"
#include "nene/math/vec2.h"
#include "nene/math/rectf.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct game_Entity {
	nene_Vec2 position;
	nene_Color color;
	nene_Vec2 size;
} game_Entity;

typedef struct game_Player {
	game_Entity as_entity;
	uint8_t entity_id;
} game_Player;

#define game_Player_SPEED (128.0f)

typedef struct game_PlayerInput {
	bool is_moving;
	nene_Vec2 moving;
} game_PlayerInput;

typedef struct game_RopeUnit {
	game_Entity as_entity;
} game_RopeUnit;

#define game_ROPE_LENGTH 8

typedef struct game_Rope {
	game_RopeUnit units[game_ROPE_LENGTH];
} game_Rope;

typedef struct game_Ball {
	game_Entity as_entity;
	nene_Vec2 velocity;
} game_Ball;

game_PlayerInput game_PlayerInput_get(uint8_t player_id) {
	game_PlayerInput result = { .is_moving = false };
	nene_Scancode left_scancode = NENE_SCANCODE_A;
	nene_Scancode right_scancode = NENE_SCANCODE_D;
	nene_Scancode up_scancode = NENE_SCANCODE_W;
	nene_Scancode down_scancode = NENE_SCANCODE_S;

	if (player_id > 2) {
		printf("WARN: player_id should be either 0 or 1\n");
		return result;
	}

	if (player_id == 1) {
			left_scancode = NENE_SCANCODE_LEFT;
			right_scancode = NENE_SCANCODE_RIGHT;
			up_scancode = NENE_SCANCODE_UP;
			down_scancode = NENE_SCANCODE_DOWN;
	}

	bool is_left_held = nene_Core_is_scancode_held(left_scancode);
	bool is_right_held = nene_Core_is_scancode_held(right_scancode);
	bool is_up_held = nene_Core_is_scancode_held(up_scancode);
	bool is_down_held = nene_Core_is_scancode_held(down_scancode);

	if (is_left_held || is_right_held || is_up_held || is_down_held) {
		result = (game_PlayerInput){
			.is_moving = true,
			.moving = (nene_Vec2){
				.x = is_left_held ? -1.0f : (is_right_held ? 1.0f : 0.0f),
				.y =   is_up_held ? -1.0f : ( is_down_held ? 1.0f : 0.0f),
			}
		};
	}

	return result;
}

game_Entity game_Entity_init(nene_Vec2 pos, nene_Color color, nene_Vec2 size) {
	return (game_Entity){
		.position = pos,
		.color = color,
		.size = size,
	};
}

void game_Entity_translate(game_Entity *const entity, nene_Vec2 translation) {
	entity->position = nene_Vec2_add(
		entity->position,
		nene_Vec2_scale(translation, nene_Core_get_delta_time())
	);
}

nene_Rectf game_Entity_bounding_box(const game_Entity *const entity) {
	return (nene_Rectf) {
		.pos = nene_Vec2_sub(
			entity->position,
			nene_Vec2_scale(
				(nene_Vec2){ .x = entity->size.x, .y = entity->size.y },
				0.5f
			)
		),
		.size = entity->size,
	};
}

void game_Entity_draw(const game_Entity *const entity) {
	nene_Core_render_draw_rect(
		nene_Rectf_to_rect(game_Entity_bounding_box(entity)),
		false,
		entity->color,
		false
	);
	nene_Core_render_draw_rect(
		(nene_Rect){ .pos = nene_Vec2_to_vec2i(entity->position), .size = {.x = 2, .y = 2 } },
		false,
		nene_Color_white(),
		false
	);
}

game_Player game_Player_init(uint8_t player_id, nene_Vec2 pos) {
	nene_Vec2 size = (nene_Vec2){ .x = 32.0f, .y = 32.0f };
	game_Player result = {
		.as_entity = game_Entity_init(pos, player_id == 0 ? nene_Color_red() : nene_Color_blue(), size),
		.entity_id = player_id,
	};
	return result;
}

void game_Player_update(game_Player *const player) {
	game_PlayerInput player_input = game_PlayerInput_get(player->entity_id);

	if (player_input.is_moving) {
		game_Entity_translate(
			&player->as_entity,
			nene_Vec2_scale(player_input.moving, game_Player_SPEED)
		);
	}
}

void game_Player_draw(const game_Player *const player) {
	game_Entity_draw(&player->as_entity);
}

void game_RopeUnit_draw(const game_RopeUnit *const rope_unit) {
	game_Entity_draw(&rope_unit->as_entity);
}

void game_RopeUnit_update(game_RopeUnit *const rope_unit, nene_Vec2 origin, nene_Vec2 ending, float i) {
	const float cf = (float)(game_ROPE_LENGTH - 1);
	rope_unit->as_entity.position = nene_Vec2_lerp(origin, ending, i / cf); 
}

void game_Rope_init(game_Rope *const rope) {
	for (int i = 0; i < game_ROPE_LENGTH; ++i) {
		rope->units[i] = (game_RopeUnit){
			.as_entity = game_Entity_init(nene_Vec2_zero(), nene_Color_white(), nene_Vec2_one())
		};
	}
}

void game_Rope_update(game_Rope *const rope, nene_Vec2 player1_pos, nene_Vec2 player2_pos) {
	for (int i = 0; i < game_ROPE_LENGTH; ++i) {
		game_RopeUnit_update(&rope->units[i], player1_pos, player2_pos, (float)i);
	}
}

void game_Rope_draw(const game_Rope *const rope) {
	for (int i = 0; i < game_ROPE_LENGTH; ++i) {
		game_RopeUnit_draw(&rope->units[i]);
	}
}

game_Ball game_Ball_init(nene_Vec2 pos) {
	return (game_Ball){
		.as_entity = game_Entity_init(
			pos,
			nene_Color_yellow(),
			(nene_Vec2){ .x = 16.0f, .y = 16.0f }
		),
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
	game_Entity_translate(&ball->as_entity, ball->velocity);
}

bool game_is_segments_intersecting(nene_Vec2 o1, nene_Vec2 e1, nene_Vec2 o2, nene_Vec2 e2) {
	// ported from Nene framework, from nene/src/intersections.c
	// "o" stands for "origin", "e" stands for "ending"
	const nene_Vec2 v1 = nene_Vec2_sub(e1, o1);
	const nene_Vec2 v2 = nene_Vec2_sub(e2, o2);
	const float cross12 = nene_Vec2_cross(v1, v2);

	if (cross12 == 0.0f) {
		return false;
	}

	const nene_Vec2 oo = nene_Vec2_sub(o2, o1);
	const float intersecting_scalar1 = nene_Vec2_cross(oo, v2) / cross12;
	const float intersecting_scalar2 = -nene_Vec2_cross(v1, oo) / cross12;

	return (
		0.0f <= intersecting_scalar1 && intersecting_scalar1 <= 1.0f &&
		0.0f <= intersecting_scalar2 && intersecting_scalar2 <= 1.0f
	);
}

bool game_Ball_is_intersecting_rope(game_Ball *const ball, nene_Vec2 ro, nene_Vec2 re) {
	// ro, re: rope origin, rope ending
	// bbo, bbe: bounding-box origin, bounding-box ending
	nene_Rectf ball_bb = game_Entity_bounding_box(&ball->as_entity);
	nene_Vec2 bbo, bbe;

	// top side
	bbo = ball_bb.pos;
	bbe = nene_Vec2_add(bbo, (nene_Vec2){ .x = ball_bb.size.x });
	if (game_is_segments_intersecting(ro, re, bbo, bbe)) {
		return true;
	}
	// right side
	bbo = bbe;
	bbe = nene_Vec2_add(bbe, (nene_Vec2){ .y = ball_bb.size.y });
	if (game_is_segments_intersecting(ro, re, bbo, bbe)) {
		return true;
	}
	// bottom side
	bbo = bbe;
	bbe = nene_Vec2_add(ball_bb.pos, (nene_Vec2){ .y = ball_bb.size.y });
	if (game_is_segments_intersecting(ro, re, bbo, bbe)) {
		return true;
	}
	// left side
	bbo = bbe;
	bbe = ball_bb.pos;
	if (game_is_segments_intersecting(ro, re, bbo, bbe)) {
		return true;
	}

	return false;
}

void game_Ball_update(game_Ball *const ball, nene_Vec2 p1, nene_Vec2 p2) {
	game_Ball_apply_gravity(ball, 48.0f);

	if (game_Ball_is_intersecting_rope(ball, p1, p2)) {
		nene_Vec2 rope_perp = nene_Vec2_normalize(nene_Vec2_perpendicular(nene_Vec2_sub(p2, p1)));

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
	game_Entity_draw(&ball->as_entity);
}

#define game_PLAYER_COUNT 2
game_Player game_players[game_PLAYER_COUNT];
game_Ball game_ball;
game_Rope game_rope;

int main(int argc, char *argv[]) {
	game_ball = game_Ball_init((nene_Vec2){ .x = 350.0f, .y = 100.0f });
	game_players[0] = game_Player_init(0, (nene_Vec2){ .x = 250.0f, .y = 500.0f });
	game_players[1] = game_Player_init(1, (nene_Vec2){ .x = 450.0f, .y = 500.0f });

	game_Rope_init(&game_rope);

	bool ok = nene_Core_init("Make me Laugh Prototype", 800, 600, NENE_WINDOW_FLAG_SHOWN);

	if (!ok) {
		return EXIT_FAILURE;
	}

	do {
		nene_Core_update();

		for (int i = 0; i < game_PLAYER_COUNT; ++i) {
			game_Player_update(&game_players[i]);
		}
		game_Rope_update(&game_rope, game_players[0].as_entity.position, game_players[1].as_entity.position);
		game_Ball_update(&game_ball, game_players[0].as_entity.position, game_players[1].as_entity.position);

		nene_Core_render_clear(nene_Color_black());

		for (int i = 0; i < game_PLAYER_COUNT; i++) {
			game_Player_draw(&game_players[i]);
		}
		game_Rope_draw(&game_rope);
		game_Ball_draw(&game_ball);

		nene_Core_render_present();
	} while (!nene_Core_should_quit());

	nene_Core_terminate();

	return EXIT_SUCCESS;
}
