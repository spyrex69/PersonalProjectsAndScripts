//2 dimensional fluid simulation prototype in object oriented.
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

const int N = 50;
const int iter = 4;
const int SQRSIZE = 5;
const float maxvelocity = 90.f;

int mousePrevX = 0, mousePrevY = 0;

int IX(int x, int y) { // formula for calculating a 2d location in a 1D array
	return (x + (N*y));
}
sf::RenderWindow window(sf::VideoMode(N*SQRSIZE, N*SQRSIZE), "Prototype", sf::Style::Titlebar | sf::Style::Close);

class FluidBox {
	int size;
	float diffusion;
	float viscocity;
	float deltatime;

	// dynamic array
	std::vector<float> pdensity;   //pri den
	std::vector<float> density;   //current den
	std::vector<float> Vx;    // current horizontal velocity 
	std::vector<float> Vx0; // prev horizontal velocity 
	std::vector<float> Vy; // current vertical velocity 
	std::vector<float> Vy0;// prev vertical velocity 

public:
	FluidBox(float diffusion, float deltatime, float viscocity):
		size(N), diffusion(diffusion), deltatime(deltatime), viscocity(viscocity),
		pdensity(N*N, 0.f), density(N*N, 0.f), Vx(N*N, 0.f), Vy(N*N, 0.f), Vx0(N*N, 0.f), Vy0(N*N, 0.f)
	{}

	void AddDensity(int x,int y, float amt) {
		int index = IX(x, y);
		density[index] += amt;
		
	}
	void AddVelocity(int x, int y, float amtx, float amty) {
		int index = IX(x, y);
		Vx[index] += amtx;
		Vy[index] += amty;
	}
	void renderDensity(sf::RenderTarget& target) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				float d = density[IX(i, j)];
				sf::RectangleShape box(sf::Vector2f(SQRSIZE, SQRSIZE));
				//density value corresponding with //opacity of current box in grid aka screen
				box.setFillColor(sf::Color(255, 255, 255, std::max(0, std::min(int(d*255), 255)) )); 
				box.setPosition(i * SQRSIZE, j * SQRSIZE);
				target.draw(box);
			}
		}
	}
	//For handling sides and corners so water doesnt leak out of box
	 void set_bnd(int b, std::vector<float>& x) {
		 //for horizontal sides of box
		for (int i = 0; i < N - 1; i++) {
				x[IX(i, 0)] = b == 2 ? -x[IX(i, 1)] : x[IX(i, 1)];
				x[IX(i, N - 1)] = b == 2 ? -x[IX(i, N - 2)] : x[IX(i, N - 2)];
			}
		//for verticals sides of box
		for (int j = 0; j< N-1; j++) {
			x[IX(0, j)] = b == 1 ? -x[IX(1, j)] : x[IX(1, j)];
			x[IX(N - 1, j)] = b == 1 ? -x[IX(N - 2, j)] : x[IX(N - 2, j)];
		}
		//for the four corners
		x[IX(0, 0)] = 0.5 * (x[IX(1, 0)] + x[IX(0, 1)]);
		x[IX(0, N - 1)] = 0.5 * (x[IX(1, N - 1)] + x[IX(0, N - 2)]);
		x[IX(N - 1, 0)] = 0.5 * (x[IX(N - 2, 0)] + x[IX(N - 1, 1)]);
		x[IX(N - 1, N - 1)] = 0.5 * (x[IX(N - 2, N - 1)] + x[IX(N - 1, N - 2)]);

	}
	void lin_solve(int b, std::vector <float>& x, std::vector <float>& x0, float a, float c) {
		float cRecip = 1.0 / c;
		for (int k = 0; k < iter; k++) {
				for (int j = 1; j < N - 1; j++) {
					for (int i = 1; i < N - 1; i++) {
						x[IX(i, j)] =
							(x0[IX(i, j)]
								+ a * (x[IX(i + 1, j)]
									+ x[IX(i - 1, j)]
									+ x[IX(i, j + 1)]
									+ x[IX(i, j - 1)])) * cRecip;
					}
				}
			set_bnd(b, x);
		}
	}

	void diffuse(int b, std::vector <float>& x, std::vector <float>& x0, float diff, float dt) {
		float a = dt * diff * (N - 2) * (N - 2);
		lin_solve(b, x, x0, a, 1 + 4 * a);
	}
	//Divergence clearence
	void project(std::vector <float>& Vx, std::vector <float>& Vy, std::vector <float>& p, std::vector <float>& divergence) {
		for (int j = 1; j < N-1; j++) {
			for (int i = 1; i < N-1; i++) {
				divergence[IX(i, j)] = -0.5f * (Vx[IX(i + 1, j)] - Vx[IX(i - 1, j)] + Vy[IX(i, j + 1)] - Vy[IX(i, j - 1)]) / N;
				p[IX(i, j)] = 0;
			}
		}
		set_bnd(0, divergence);
		set_bnd(0, p);
		lin_solve(0, p, divergence, 1, 6);

		for (int j = 1; j < N-1; j++) {
			for (int i = 1; i < N-1; i++) {
				Vx[IX(i, j)] -= 0.5f * (p[IX(i + 1, j)]
					- p[IX(i - 1, j)]) * N;
				Vy[IX(i, j)] -= 0.5f * (p[IX(i, j + 1)]
					- p[IX(i, j - 1)]) * N;
			}
		}
		set_bnd(1, Vx);
		set_bnd(2, Vy);
	}

    void advect(int b, std::vector <float>& d, std::vector <float>& d0, std::vector <float>& Vx, std::vector <float>& Vy, float dt) {
		float i0, i1, j0, j1;

        float dtx = dt * (N - 2);
        float dty = dt * (N - 2);

        float s0, s1, t0, t1;
        float tmp1, tmp2, x, y;

        float Nfloat = N;
        float ifloat, jfloat;
        int i, j;

        for (j = 1, jfloat = 1; j < N - 1; j++, jfloat++) {
            for (i = 1, ifloat = 1; i < N - 1; i++, ifloat++) {
                tmp1 = dtx * Vx[IX(i, j)];
                tmp2 = dty * Vy[IX(i, j)];

                x = std::fmin(std::fmax(0.5f, ifloat - tmp1), Nfloat + 0.5f);
                y = std::fmin(std::fmax(0.5f, jfloat - tmp2), Nfloat + 0.5f);

                i0 = floor(x);
                i1 = i0 + 1.0f;
                j0 = floor(y);
                j1 = j0 + 1.0f;

                s1 = x - i0;
                s0 = 1.0f - s1;
                t1 = y - j0;
                t0 = 1.0f - t1;

                int i0i = int(i0);
                int i1i = int(i1);
                int j0i = int(j0);
                int j1i = int(j1);

                d[IX(i, j)] = s0 * (t0 * d0[IX(i0i, j0i)] + t1 * d0[IX(i0i, j1i)]) +
                    s1 * (t0 * d0[IX(i1i, j0i)] + t1 * d0[IX(i1i, j1i)]);
            }
        }

        set_bnd(b, d);
	}

	void step(float delta) {

		//step1 diffusing the velocities based on viscocity and time period
		diffuse(1, Vx0, Vx, viscocity, deltatime * delta);
		diffuse(2, Vy0, Vy, viscocity, deltatime * delta);

		//step2 clearing the divergnce for velociy to bring equilibrium
		project(Vx0, Vy0, Vx, Vy);

		//step3 advectuing the velocites
		advect(1, Vx, Vx0, Vx0, Vy0, deltatime * delta);
		advect(2, Vy, Vy0, Vx0, Vy0, deltatime * delta);

		//step4 clearing the advention divergence
		project(Vx, Vy, Vx0, Vy0);

		//step5 Diffsuing and advecting the densities
		diffuse(0, pdensity, density, diffusion, deltatime * delta);

		advect(0, density, pdensity, Vx, Vy, deltatime * delta);
	}
};

int main() {
	FluidBox fluid(0.005, 0.8, 0.00001);
	sf::Clock FPS;
	while (window.isOpen()) {
		int mouseX = sf::Mouse::getPosition(window).x,
			mouseY = sf::Mouse::getPosition(window).y,
			xx = std::max(1, std::min(N-2, mouseX / SQRSIZE)),
			yy = std::max(1, std::min(N-2, mouseY / SQRSIZE)),
			px = std::max(1, std::min(N-2, mousePrevX / SQRSIZE)),
			py = std::max(1, std::min(N-2, mousePrevY / SQRSIZE));
		float spd = 25.f;

		sf::Event ent;
		while(window.pollEvent(ent)) {
			if (ent.type == ent.Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()) {
			fluid.AddDensity(xx, yy, 0.8);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)){
			spd *= 3;
		}

		fluid.AddVelocity(xx, yy, std::fmax(std::fmin(float(xx - px) * spd, maxvelocity), -maxvelocity), std::fmax(std::fmin(float(yy - py) * spd, maxvelocity), -maxvelocity));


		fluid.step(FPS.getElapsedTime().asSeconds()); //fluid phyuscis logic funtion

		// ------------------ changes ----------------------
		window.clear(); // Clear the window before drawing
		// All the current frame's drawing goes here
		fluid.renderDensity(window);

		mousePrevX = mouseX;
		mousePrevY = mouseY;

		FPS.restart();
		window.display(); // display the window only once per frame
	}
	return 0;
}