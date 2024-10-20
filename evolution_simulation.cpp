#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <cstdlib> 
#include <algorithm> 
#include <limits>
#include <ctime>

enum class Emotion { Stressed, Neutral, Calm };  // New emotion states

class Entity {
public:
    double consciousnessLevel;
    double knowledgeLevel;
    Emotion emotionalState;        // Emotional state of the entity
    double adaptability;           // How well the entity adapts to changes
    double decisionMaking;         // Ability to make decisions
    double interactionAbility;     // Ability to interact with other entities

    Entity() {
        consciousnessLevel = generateRandomLevel();
        knowledgeLevel = generateRandomLevel();
        emotionalState = Emotion::Neutral;
        adaptability = generateRandomLevel();
        decisionMaking = generateRandomLevel();
        interactionAbility = generateRandomLevel();
    }

    // Method to evolve the entity's attributes
    void evolve(double environmentComplexity, const std::vector<Entity>& otherEntities, int index) {
        try {
            // Adjust emotion based on the environment
            adjustEmotion(environmentComplexity);

            // Interact with other entities and influence adaptability/decision-making
            interactWithOthers(otherEntities, index);

            // Evolve consciousness and knowledge levels based on emotional state and adaptability
            consciousnessLevel = evolveConsciousness(consciousnessLevel, adaptability, emotionalState);
            knowledgeLevel = evolveKnowledge(knowledgeLevel, adaptability, emotionalState);

            // Cap values to prevent overflow
            capValues();
        } catch (const std::exception& e) {
            std::cerr << "Error during evolution: " << e.what() << std::endl;
        }
    }

    // Method to print the current status of the entity
    void printStatus(int step) const {
        std::cout << "Step " << step 
                  << " | Consciousness: " << consciousnessLevel 
                  << " | Knowledge: " << knowledgeLevel
                  << " | Emotion: " << getEmotionString() 
                  << " | Adaptability: " << adaptability
                  << " | Decision Making: " << decisionMaking
                  << " | Interaction: " << interactionAbility << std::endl;
    }

private:
    // Method to generate a random value between 0 and 1
    double generateRandomLevel() {
        return static_cast<double>(rand()) / RAND_MAX;
    }

    // Adjust emotional state based on environmental complexity
    void adjustEmotion(double environmentComplexity) {
        if (environmentComplexity > 0.7) {
            emotionalState = Emotion::Stressed;
        } else if (environmentComplexity > 0.3) {
            emotionalState = Emotion::Neutral;
        } else {
            emotionalState = Emotion::Calm;
        }
    }

    // Method to evolve consciousness based on adaptability and emotional state
    double evolveConsciousness(double level, double adaptability, Emotion emotion) {
        double growthFactor = 0.1 * (1 - level) * adaptability;
        if (emotion == Emotion::Stressed) growthFactor *= 0.7;
        else if (emotion == Emotion::Calm) growthFactor *= 1.2;
        return std::min(1.0, level + growthFactor);
    }

    // Method to evolve knowledge based on adaptability and emotional state
    double evolveKnowledge(double level, double adaptability, Emotion emotion) {
        double growthFactor = 0.05 * (1 - level) * adaptability;
        if (emotion == Emotion::Stressed) growthFactor *= 0.7;
        else if (emotion == Emotion::Calm) growthFactor *= 1.2;
        return std::min(1.0, level + growthFactor);
    }

    // Method to interact with other entities and adjust adaptability and decision-making
    void interactWithOthers(const std::vector<Entity>& otherEntities, int index) {
        for (size_t i = 0; i < otherEntities.size(); ++i) {
            if (i != index) {  // Avoid self-interaction
                const Entity& other = otherEntities[i];
                if (other.emotionalState == Emotion::Stressed) {
                    adaptability = std::max(0.1, adaptability * 0.9);  // Avoid 0 or negative adaptability
                    decisionMaking = std::max(0.1, decisionMaking * 0.9);  // Avoid 0 or negative decision-making
                } else if (other.emotionalState == Emotion::Calm) {
                    adaptability = std::min(1.0, adaptability * 1.1);  // Cap values at 1
                    decisionMaking = std::min(1.0, decisionMaking * 1.1);
                }
            }
        }
    }

    // Method to cap values between 0 and 1
    void capValues() {
        consciousnessLevel = std::min(1.0, std::max(0.0, consciousnessLevel));
        knowledgeLevel = std::min(1.0, std::max(0.0, knowledgeLevel));
        adaptability = std::min(1.0, std::max(0.0, adaptability));
        decisionMaking = std::min(1.0, std::max(0.0, decisionMaking));
        interactionAbility = std::min(1.0, std::max(0.0, interactionAbility));
    }

    // Method to get emotion as a string
    std::string getEmotionString() const {
        switch (emotionalState) {
            case Emotion::Stressed: return "stressed";
            case Emotion::Neutral: return "neutral";
            case Emotion::Calm: return "calm";
            default: return "unknown";
        }
    }
};

// Main simulation loop
int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator

    try {
        const int numEntities = 5;  // Number of entities in the simulation
        const int numSteps = 100;   // Number of simulation steps
        std::vector<Entity> entities(numEntities);
        double environmentComplexity = 0.5;  // Initial environment complexity

        for (int step = 1; step <= numSteps; ++step) {
            // Change the environment complexity every 10 steps for dynamic behavior
            if (step % 10 == 0) {
                environmentComplexity = static_cast<double>(rand()) / RAND_MAX;
                std::cout << "Environment complexity changed to: " << environmentComplexity << std::endl;
            }

            std::cout << "----- Simulation Step " << step << " -----" << std::endl;
            for (int i = 0; i < numEntities; ++i) {
                entities[i].evolve(environmentComplexity, entities, i);  // Pass the index to avoid self-interaction
                entities[i].printStatus(step);  // Print the status of each entity
            }
            std::cout << "----------------------------------" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Simulation encountered an error: " << e.what() << std::endl;
    }

    return 0;
}
