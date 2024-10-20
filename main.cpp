#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <cstdlib> // For rand()
#include <algorithm> // For std::min
#include <limits> // For numeric limits on floating points

class Entity {
public:
    double consciousnessLevel;
    double knowledgeLevel;

    Entity() {
        consciousnessLevel = generateRandomLevel();
        knowledgeLevel = generateRandomLevel();
    }

    void evolve() {
        try {
            // Simulate evolution by increasing consciousness and knowledge levels
            consciousnessLevel = evolveConsciousness(consciousnessLevel);
            knowledgeLevel = evolveKnowledge(knowledgeLevel);

            // Safeguard against floating-point precision issues near 1.0
            if (std::abs(1.0 - consciousnessLevel) < std::numeric_limits<double>::epsilon()) {
                consciousnessLevel = 1.0;
            }
            if (std::abs(1.0 - knowledgeLevel) < std::numeric_limits<double>::epsilon()) {
                knowledgeLevel = 1.0;
            }

        } catch (const std::exception &e) {
            std::cerr << "Error during evolution: " << e.what() << std::endl;
        }
    }

    void printStatus(int step) const {
        std::cout << "Consciousness Level: " << consciousnessLevel 
                  << " | Knowledge Level: " << knowledgeLevel << std::endl;
    }

private:
    // Generates a random level between 0 and 1
    double generateRandomLevel() {
        return static_cast<double>(rand()) / RAND_MAX;
    }

    // Simulates the evolution of consciousness
    double evolveConsciousness(double level) {
        if (level < 0 || level > 1) throw std::invalid_argument("Invalid consciousness level");
        double newLevel = level + 0.1 * (1 - level);  // Logarithmic growth
        return std::min(1.0, newLevel);  // Cap the value at 1.0
    }

    // Simulates the evolution of knowledge
    double evolveKnowledge(double level) {
        if (level < 0 || level > 1) throw std::invalid_argument("Invalid knowledge level");
        double newLevel = level + 0.05 * (1 - level);  // Slower growth for knowledge
        return std::min(1.0, newLevel);  // Cap the value at 1.0
    }
};

int main() {
    try {
        const int numEntities = 5;    // Number of entities in the simulation
        const int numSteps = 175;     // Number of simulation steps
        std::vector<Entity> entities(numEntities);

        for (int step = 1; step <= numSteps; ++step) {
            std::cout << "----- Simulation Step " << step << " -----" << std::endl;
            
            for (Entity& entity : entities) {
                entity.evolve();
                entity.printStatus(step);
            }

            std::cout << "----------------------------------" << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Simulation encountered an error: " << e.what() << std::endl;
    }

    return 0;
}
