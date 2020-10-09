const TILE_SIZE = 64;
const MAP_NUM_ROWS = 11;
const MAP_NUM_COLS = 15;

const WINDOW_WIDTH = MAP_NUM_COLS * TILE_SIZE;
const WINDOW_HEIGHT = MAP_NUM_ROWS * TILE_SIZE;

const FOV_ANGLE = 60 * (Math.PI / 180);

const WALL_STRIP_WIDTH = 3;
const NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

const MINIMAP_SCALE_FACTOR = 0.2;

class Map {
    constructor() {
        this.grid = [
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1],
            [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
        ];
	}
	hasWall(x, y) {
		if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
			return (true);
		var mapGridIndexX = Math.floor(x / TILE_SIZE);
		var mapGridIndexY = Math.floor(y / TILE_SIZE);
		return (this.grid[mapGridIndexY][mapGridIndexX] == 1);
	}
    render() {
        for (var i = 0; i < MAP_NUM_ROWS; i++) {
            for (var j = 0; j < MAP_NUM_COLS; j++) {
                var tileX = j * TILE_SIZE; 
                var tileY = i * TILE_SIZE;
                var tileColor = this.grid[i][j] == 1 ? "#222" : "#fff";
                stroke("#222");
                fill(tileColor);
                rect(
					MINIMAP_SCALE_FACTOR * tileX,
					MINIMAP_SCALE_FACTOR * tileY,
					MINIMAP_SCALE_FACTOR * TILE_SIZE,
					MINIMAP_SCALE_FACTOR * TILE_SIZE
				);
            }
        }
    }
}

class Player {
	constructor() {
		this.x = WINDOW_WIDTH / 2;
		this.y = WINDOW_HEIGHT / 2;
		this.radius = 3;
		this.turnDirection = 0; // -1 if left, +1 if right
		this.walkDirection = 0; // -1 if back, +1 if front
		this.rotationAngle = Math.PI / 2;
		this.moveSpeed = 2.0;
		this.rotationSpeed = 2 * (Math.PI / 180);
	}
	update() {
		this.rotationAngle += this.turnDirection * this.rotationSpeed;

		var moveStep = this.walkDirection * this.moveSpeed;

		var newPlayerX = this.x + moveStep * Math.cos(this.rotationAngle);
		var newPlayerY = this.y + moveStep * Math.sin(this.rotationAngle);
		if (!grid.hasWall(newPlayerX, newPlayerY)) {
			this.x = newPlayerX;
			this.y = newPlayerY;
		}
	}
	render() {
		noStroke();
		fill("red");
		circle(
			MINIMAP_SCALE_FACTOR * this.x,
			MINIMAP_SCALE_FACTOR * this.y,
			MINIMAP_SCALE_FACTOR * this.radius
		);
		// stroke("red");
		// line (
		// 	this.x,
		// 	this.y,
		// 	this.x + Math.cos(this.rotationAngle) * 20,
		// 	this.y + Math.sin(this.rotationAngle) * 20
		// )
	}
}

class Ray {
	constructor(rayAngle) {
		this.rayAngle = normalizeAngle(rayAngle);
		this.wallHitX = 0;
		this.wallHitY = 0;
		this.distance = 0;
		this.wasHitVertical = false;

		this.isRayFacingDown = this.rayAngle > 0 && this.rayAngle < Math.PI;
		this.isRayFacingUp = !this.isRayFacingDown;

		this.isRayFacingRight = this.rayAngle < 0.5 * Math.PI || this.rayAngle > 1.5 * Math.PI;
		this.isRayFacingLeft = !this.isRayFacingRight;
	}
	cast(columnId) {
		var xintercept, yintercept;
		var xstep, ystep;

		//HORIZOZNTAL RAY-Grid intersection code
		var foundHorzWallHit = false;
		var horzWallHitX = 0;
		var horzWallHitY = 0;

		yintercept = Math.floor(player.y / TILE_SIZE) * TILE_SIZE;
		yintercept += this.isRayFacingDown ? TILE_SIZE : 0;

		xintercept = player.x + (yintercept - player.y) / Math.tan(this.rayAngle);

		ystep = TILE_SIZE;
		ystep *= this.isRayFacingUp ? -1 : 1;

		xstep = TILE_SIZE / Math.tan(this.rayAngle);
		xstep *= (this.isRayFacingLeft && xstep > 0) ? -1 : 1;
		xstep *= (this.isRayFacingRight && xstep < 0) ? -1 : 1;

		var nextHorzTouchX = xintercept;
		var nextHorzTouchY = yintercept;

		while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) {
			if (grid.hasWall(nextHorzTouchX, nextHorzTouchY - (this.isRayFacingUp ? 1 : 0))) {
				foundHorzWallHit = true;
				horzWallHitX = nextHorzTouchX;
				horzWallHitY = nextHorzTouchY;

				break;
			}
			else {
				nextHorzTouchX += xstep;
				nextHorzTouchY += ystep;
			}
		}

		//VERTICAL RAY-Grid intersection code
		var foundVertWallHit = false;
		var vertWallHitX = 0;
		var vertWallHitY = 0;

		xintercept = Math.floor(player.x / TILE_SIZE) * TILE_SIZE;
		xintercept += this.isRayFacingRight ? TILE_SIZE : 0;

		yintercept = player.y + (xintercept - player.x) * Math.tan(this.rayAngle);

		xstep = TILE_SIZE;
		xstep *= this.isRayFacingLeft ? -1 : 1;

		ystep = TILE_SIZE * Math.tan(this.rayAngle);
		ystep *= (this.isRayFacingUp && ystep > 0) ? -1 : 1;
		ystep *= (this.isRayFacingDown && ystep < 0) ? -1 : 1;

		var nextVertTouchX = xintercept;
		var nextVertTouchY = yintercept;

		while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) {
			if (grid.hasWall(nextVertTouchX - (this.isRayFacingLeft ? 1 : 0), nextVertTouchY)) {
				foundVertWallHit = true;
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;

				break;
			}
			else {
				nextVertTouchX += xstep;
				nextVertTouchY += ystep;
			}
		}

		//二つの直線を比較して短い方を使う
		var horzHitDistance = (foundHorzWallHit)
			? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
			: Number.MAX_VALUE;
		var vertHitDistance = (foundVertWallHit)
			? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
			: Number.MAX_VALUE;
		
		this.wallHitX = horzHitDistance < vertHitDistance ? horzWallHitX : vertWallHitX;
		this.wallHitY = horzHitDistance < vertHitDistance ? horzWallHitY : vertWallHitY;
		this.distance = horzHitDistance < vertHitDistance ? horzHitDistance : vertHitDistance;
		this.wasHitVertical = horzHitDistance > vertHitDistance;
	}
	render() {
		stroke("rgba(0, 255, 0, 0.4)");
		line(
			MINIMAP_SCALE_FACTOR * player.x,
			MINIMAP_SCALE_FACTOR * player.y,
			MINIMAP_SCALE_FACTOR * this.wallHitX,
			MINIMAP_SCALE_FACTOR * this.wallHitY
		);
	}
}

var grid = new Map();
var player = new Player();
var rays = [];

function normalizeAngle(angle) {
	angle = angle % (2 * Math.PI);
	if (angle < 0) {
		angle += Math.PI * 2;
	}
	return (angle);
}

function keyPressed() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 1;
	} else if (keyCode == DOWN_ARROW) {
		player.walkDirection = -1;
	} else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 1;
	} else if (keyCode == LEFT_ARROW) {
		player.turnDirection = -1;
	}
}

function keyReleased() {
	if (keyCode == UP_ARROW) {
		player.walkDirection = 0;
	} else if (keyCode == DOWN_ARROW) {
		player.walkDirection = 0;
	} else if (keyCode == RIGHT_ARROW) {
		player.turnDirection = 0;
	} else if (keyCode == LEFT_ARROW) {
		player.turnDirection = 0;
	}
}

function castAllRays() {
	var columnId = 0;

	//start first ray subtracting half of the FOV
	var rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

	rays = [];

	for (var i = 0; i < NUM_RAYS; i++) {
		var ray = new Ray(rayAngle);
		ray.cast(columnId);
		rays.push(ray);

		rayAngle += FOV_ANGLE / NUM_RAYS;

		columnId++;
	}
}

function render3DProjectedWalls() {
	for (var i = 0; i < NUM_RAYS; i++) {
		var ray = rays[i];

		var correctWallDistance = ray.distance * Math.cos(ray.rayAngle - player.rotationAngle);

		var distanceProjectionPlane = (WINDOW_WIDTH / 2) / Math.tan(FOV_ANGLE / 2);

		var wallStripHeight = (TILE_SIZE / correctWallDistance) * distanceProjectionPlane;

		// fill("rgba(255, 255, 255, 1.0)");
		// fill(255 - correctWallDistance * 0.2,
		// 	255 - correctWallDistance * 0.2,
		// 	255 - correctWallDistance * 0.2
		// );
		fill(255 - ray.distance * 0.2,
			255 - ray.distance * 0.2,
			255 - ray.distance * 0.2
		);
		noStroke();
		rect(
			i * WALL_STRIP_WIDTH,
			(WINDOW_HEIGHT / 2) - (wallStripHeight / 2),
			WALL_STRIP_WIDTH,
			wallStripHeight
		);
	}

}

function distanceBetweenPoints(x1, y1, x2, y2) {
	return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

function setup() {
    createCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
}

function update() {
	player.update();
	castAllRays();
}

function draw() {
	clear("#212121");
	update();
	
	render3DProjectedWalls();

	grid.render();
	for (ray of rays) {
		ray.render();
	}
	player.render();
}
