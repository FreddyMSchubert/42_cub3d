/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:22:19 by freddy            #+#    #+#             */
/*   Updated: 2024/05/24 18:05:55 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

double	pos_distance(t_vec2 pos1, t_vec2 pos2)
{
	return (sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)));
}

// makes the rot of a vector as long as possible keeping the same relative value
t_transform	infinitify_transform(t_transform t1)
{
	double	scale_factor;

	scale_factor = DBL_MAX / fmax(fabs(t1.rot.x), fabs(t1.rot.y));
	t1.rot.x *= scale_factor;
	t1.rot.y *= scale_factor;
	return (t1);
}

t_vec2	*raycast_intersect(t_transform t1, t_transform t2)
{
	double	denom;
	double	t;
	double	u;
	t_vec2	*intersection;

	denom = t1.rot.x * t2.rot.y - t1.rot.y * t2.rot.x;
	if (denom == 0.0)
		return (NULL);
	t = ((t2.pos.x - t1.pos.x) * t2.rot.y - \
		(t2.pos.y - t1.pos.y) * t2.rot.x) / denom;
	u = ((t2.pos.x - t1.pos.x) * t1.rot.y - \
		(t2.pos.y - t1.pos.y) * t1.rot.x) / denom;
	if (t >= 0.0 && u >= 0.0 && u <= 1.0)
	{
		intersection = (t_vec2 *)malloc(sizeof(t_vec2));
		intersection->x = t1.pos.x + t * t1.rot.x;
		intersection->y = t1.pos.y + t * t1.rot.y;
		return (intersection);
	}
	return (NULL);
}

/*
void test_case(t_transform t1, t_transform t2)
{
	t_vec2 *intersection = raycast_intersect(t1, t2);
	if (intersection) {
		printf("Intersection at: (%f, %f)\n", intersection->x, intersection->y);
		free(intersection);
	} else {
		printf("No intersection found.\n");
	}
}

int main()
{
	t_transform t1_case1 = {{0, 0}, {1, 1}};
	t_transform t2_case1 = {{1, 0}, {0, 2}};
	printf("Case 1:\n");
	test_case(t1_case1, t2_case1);  // Expected: (1, 1)

	t_transform t1_case2 = {{0, 0}, {1, 1}};
	t_transform t2_case2 = {{3, 0}, {0, 4}};
	printf("Case 2:\n");
	test_case(t1_case2, t2_case2);  // Expected: (3, 3)

	t_transform t1_case3 = {{0, 0}, {1, 0}};
	t_transform t2_case3 = {{0, 1}, {2, 0}};
	printf("Case 3:\n");
	test_case(t1_case3, t2_case3);  // Expected: No intersection

	t_transform t1_case4 = {{0, 0}, {1, 0}};
	t_transform t2_case4 = {{-1, 0}, {2, 0}};
	printf("Case 4:\n");
	test_case(t1_case4, t2_case4);  // Expected: No intersection

	t_transform t1_case5 = {{0, 0}, {0, 1}};
	t_transform t2_case5 = {{-1, 1}, {2, 0}};
	printf("Case 5:\n");
	test_case(t1_case5, t2_case5);  // Expected: (0, 1)

	return 0;
}

*/

// check back of the ray intersection
