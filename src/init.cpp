#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_memory_editor.h>
#include <cstring> 
#include <nfd.h>

#include "../include/grid.h"
#include "../include/cpu.h"
#include "../include/opcode.h"
#include "../include/init.h"


// Déclaration des variables globales
const int Window_Width = static_cast<int>(1920 / 1.5);  // Calcul avec casting pour éviter les erreurs
const int Window_Height = static_cast<int>(1080 / 1.5); // Calcul avec casting pour éviter les erreurs

const int Y = 19;




void Chip8::Emulation(int argc, char** argv, bool alredy_game, const char* game_name, bool Step) 
{

    bool Step_par_Step = Step;
    // Historique des opcodes
    std::vector<std::pair<uint16_t, uint16_t>> opcodeHistory;
    const int maxHistorySize = 6;

    (void) argc;
    (void) argv;


    Grid grid = Grid();
    CPU cpu = CPU();
    opcode op;

    if (alredy_game) {
        cpu.GameName = game_name;
        cpu.loadGame(cpu.GameName);
        op.initializeOpcodeMask();
        grid.initialize();  

  
    }


    // Initialiser SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SDL_Window* window = SDL_CreateWindow("Chip8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Window_Width, Window_Height, 0);
    if (window == nullptr) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == nullptr) {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {

        std::cout << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
    }

    // Initialiser ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void) io;
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);



        // Gestion des FPS:
    const int FPS = 240;  // 240
    const int frameDelay = 1000 / FPS; // Délai pour chaque frame en millisecondes

    bool run = true;
    while (run) {
        Uint32 frameStart = SDL_GetTicks(); // Temps de début de la frame
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                run = false;
            }
    /*---------------------------------------------------------------------------------------------*/
    switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        std::cout << "Touche presse : ESC" << std::endl;
                        break;

                    case SDLK_KP_7:
                        cpu.touche[0x0] = 1;
                        std::cout << "Touche presse : 1" << std::endl;
                        break;

                    case SDLK_KP_8:
                        cpu.touche[0x1] = 1;
                        std::cout << "Touche presse : 2" << std::endl;
                        break;

                    case SDLK_KP_9:
                        cpu.touche[0x2] = 1;
                        std::cout << "Touche presse : 3" << std::endl;
                        break;

                    case SDLK_KP_4:
                        cpu.touche[0x4] = 1;
                        std::cout << "Touche presse : 4" << std::endl;
                        break;

                    case SDLK_KP_5:
                        cpu.touche[0x5] = 1;
                        std::cout << "Touche presse : 5" << std::endl;
                        break;

                    case SDLK_KP_6:
                        cpu.touche[0x6] = 1;
                        std::cout << "Touche presse : 6" << std::endl;
                        break;

                    case SDLK_KP_MULTIPLY:
                        cpu.touche[0x7] = 1;
                        std::cout << "Touche presse : D" << std::endl;
                        break;

                    case SDLK_KP_1:
                        cpu.touche[0x8] = 1;
                        std::cout << "Touche presse : 7" << std::endl;
                        break;

                    case SDLK_KP_2:
                        cpu.touche[0x9] = 1;
                        std::cout << "Touche presse : 8" << std::endl;
                        break;

                    case SDLK_KP_3:
                        cpu.touche[0xA] = 1;
                        std::cout << "Touche presse : 9" << std::endl;
                        break;

                    case SDLK_KP_MINUS:
                        cpu.touche[0xB] = 1;
                        std::cout << "Touche presse : E" << std::endl;
                        break;

                    case SDLK_RIGHT:
                        cpu.touche[0xC] = 1;
                        std::cout << "Touche presse : A" << std::endl;
                        break;

                    case SDLK_KP_0:
                        cpu.touche[0xD] = 1;
                        std::cout << "Touche presse : 0" << std::endl;
                        break;

                    case SDLK_KP_PERIOD:
                        cpu.touche[0xE] = 1;
                        std::cout << "Touche presse : B" << std::endl;
                        break;

                    case SDLK_KP_PLUS:
                        cpu.touche[0xF] = 1;
                        std::cout << "Touche presse : F" << std::endl;
                        break;

                    default:
                        std::cout << "Touche presse : " << event.key.keysym.sym << std::endl;
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_KP_7:
                        cpu.touche[0x0] = 0;
                        std::cout << "Touche relâchée : 1" << std::endl;
                        break;

                    case SDLK_KP_8:
                        cpu.touche[0x1] = 0;
                        std::cout << "Touche relâchée : 2" << std::endl;
                        break;

                    case SDLK_KP_9:
                        cpu.touche[0x2] = 0;
                        std::cout << "Touche relâchée : 3" << std::endl;
                        break;

                    case SDLK_KP_4:
                        cpu.touche[0x4] = 0;
                        std::cout << "Touche relâchée : 4" << std::endl;
                        break;

                    case SDLK_KP_5:
                        cpu.touche[0x5] = 0;
                        std::cout << "Touche relâchée : 5" << std::endl;
                        break;

                    case SDLK_KP_6:
                        cpu.touche[0x6] = 0;
                        std::cout << "Touche relâchée : 6" << std::endl;
                        break;

                    case SDLK_KP_MULTIPLY:
                        cpu.touche[0x7] = 0;
                        std::cout << "Touche relâchée : D" << std::endl;
                        break;

                    case SDLK_KP_1:
                        cpu.touche[0x8] = 0;
                        std::cout << "Touche relâchée : 7" << std::endl;
                        break;

                    case SDLK_KP_2:
                        cpu.touche[0x9] = 0;
                        std::cout << "Touche relâchée : 8" << std::endl;
                        break;

                    case SDLK_KP_3:
                        cpu.touche[0xA] = 0;
                        std::cout << "Touche relâchée : 9" << std::endl;
                        break;

                    case SDLK_KP_MINUS:
                        cpu.touche[0xB] = 0;
                        std::cout << "Touche relâchée : E" << std::endl;
                        break;

                    case SDLK_RIGHT:
                        cpu.touche[0xC] = 0;
                        std::cout << "Touche relâchée : A" << std::endl;
                        break;

                    case SDLK_KP_0:
                        cpu.touche[0xD] = 0;
                        std::cout << "Touche relâchée : 0" << std::endl;
                        break;

                    case SDLK_KP_PERIOD:
                        cpu.touche[0xE] = 0;
                        std::cout << "Touche relâchée : B" << std::endl;
                        break;

                    case SDLK_KP_PLUS:
                        cpu.touche[0xF] = 0;
                        std::cout << "Touche relâchée : F" << std::endl;
                        break;

                    default:
                        std::cout << "Touche relâchée : " << event.key.keysym.sym << std::endl;
                        break;
                }
                break;

            default:
                break;
        }

    /*---------------------------------------------------------------------------------------------*/

        if (cpu.sound_timer != 0) {
            std::cout << "Beep" << std::endl;
        Mix_Chunk *son = Mix_LoadWAV("sound/beep.wav");
        if (!son) {
          std::cout << "Erreur lors de la lecture du son: " << Mix_GetError() << std::endl;

        }   

        // Lecture du son
        if (Mix_PlayChannel(-1, son, 0) == 0) {
            std::cout << "Erreur lors de la lecture du son: " << Mix_GetError() << std::endl;
        } 






        }


            ImGui_ImplSDL2_ProcessEvent(&event);
        }
        

        if (!Step_par_Step) {
            // Enregistrez l'opcode actuel dans l'historiqu

            cpu.Befor_opcode = cpu.opcode;
            cpu.opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];
            op.DecodOpcode(&cpu, cpu.opcode, &grid);
            cpu.After_opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];
            

            cpu.delay_timer -= 1;
            cpu.sound_timer -= 1;

            opcodeHistory.push_back({cpu.pc, cpu.opcode});
            if (opcodeHistory.size() > maxHistorySize) {
                opcodeHistory.erase(opcodeHistory.begin());
    
    
            }
        }



        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("Memory");

        static MemoryEditor mem_edit;
        mem_edit.DrawContents(&cpu.memory, sizeof(cpu.memory));
        

        ImGui::SetWindowSize(ImVec2(832, 304 - Y), ImGuiCond_FirstUseEver);
        ImGui::SetWindowPos(ImVec2(0, 416 + Y));


        ImGui::End();

        ImGui::Begin("Chip8 Emulator", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);        
        ImGui::Text("Very useful text");

        ImGui::Separator();

        if (ImGui::Button("Run/Stop", ImVec2(70, 20))) {
            Step_par_Step = !Step_par_Step;
        }
        
        ImGui::SameLine();
        if (ImGui::Button("Step", ImVec2(50, 20))){
   
            cpu.Befor_opcode = cpu.opcode;
            cpu.opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];
            op.DecodOpcode(&cpu, cpu.opcode, &grid);
            cpu.After_opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];
            cpu.delay_timer -= 1;
            cpu.sound_timer -= 1;

            opcodeHistory.push_back({cpu.pc, cpu.opcode});
            if (opcodeHistory.size() > maxHistorySize) {
                opcodeHistory.erase(opcodeHistory.begin());
            }

        }

        ImGui::SameLine();
        if (ImGui::Button("Reload", ImVec2(50, 20))) {
            cpu.initialize();
            cpu.loadGame(cpu.GameName);
            op.initializeOpcodeMask();
            grid.initialize();  
        }
        

        // Affichage des lignes de texte dans la zone de défilement
            
            std::string BeforOP = "Before OP: " + cpu.toHexString(cpu.Befor_opcode);
            ImGui::Text(BeforOP.c_str());


            std::string ActualOP = "Actual OP: " + cpu.toHexString(cpu.opcode);
            ImGui::Text(ActualOP.c_str());

            std::string AferOP = "After OP: " + cpu.toHexString(cpu.After_opcode);
            ImGui::Text(AferOP.c_str());

            ImGui::Text(cpu.GameName);




        ImGui::SetWindowSize(ImVec2(448, 416));
        ImGui::SetWindowPos(ImVec2(832, 0));
        ImGui::End();

// -------------------------- TEST
ImGui::Begin("Debugger");

ImGui::SetWindowSize(ImVec2(448, 304));
ImGui::SetWindowPos(ImVec2(832, 416));

        // Afficher les registres en table verticale
        ImGui::Text("Registers:");
        if (ImGui::BeginTable("RegistersTable", 4)) {
            for (int i = 0; i < 16; ++i) {
                std::string regName = "V" + std::to_string(i);
                if (i >= 10) {
                    regName = "V" + std::string(1, 'A' + (i - 10));
                }
                std::string regValue = regName + ": " + cpu.toHexString(cpu.registre[i]);
                ImGui::TableNextColumn();
                ImGui::Text("%s", regValue.c_str());
            }
            ImGui::TableNextColumn(); ImGui::Text("PC: %04X", cpu.pc);
            ImGui::TableNextColumn(); ImGui::Text("I: %04X", cpu.I);
            ImGui::TableNextColumn(); ImGui::Text("DT: %02X", cpu.delay_timer);
            ImGui::TableNextColumn(); ImGui::Text("ST: %02X", cpu.sound_timer);
            ImGui::EndTable();
        }
    
        // Afficher la pile en table verticale
        ImGui::Text("Stack:");
        if (ImGui::BeginTable("StackTable", 4)) { // Adapter le nombre de colonnes selon le besoin
            for (int i = 0; i < cpu.pile.size(); ++i) {
                ImGui::TableNextColumn();
                ImGui::Text("%04X", cpu.pile[i]);
            }
            ImGui::EndTable();
        }

        ImGui::Separator();

        // Affichage des lignes de texte dans la zone de défilement
        ImGui::Text("Historique des opcodes:");
        if (ImGui::BeginTable("OpcodeHistoryTable", 2)) {
            ImGui::TableSetupColumn("Adresse");
            ImGui::TableSetupColumn("Opcode");
            ImGui::TableHeadersRow();

            for (const auto& entry : opcodeHistory) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text("%04X", entry.first);
                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%04X", entry.second);
            }

            ImGui::EndTable();
        }

        ImGui::End();


//--------------------------------------------------- TODO

        if (ImGui::BeginMainMenuBar()) {
              if (ImGui::BeginMenu("File")) {
                   if (ImGui::MenuItem("Create")) { 
                   }
                   if (ImGui::MenuItem("Open", "Ctrl+O")) { 



                        // Déclarez un pointeur pour stocker le chemin du fichier sélectionné
                        nfdchar_t *outPath = nullptr;

                        // Ouvrez la boîte de dialogue pour sélectionner un fichier avec les extensions "ch8" et "c8"
                        nfdresult_t result = NFD_OpenDialog("ch8,c8", nullptr, &outPath);

                        // Gérer le résultat de la boîte de dialogue
                        switch (result) {
                            case NFD_OKAY:
                                std::cout << "Fichier sélectionné: " << outPath << std::endl;
                                cpu.GameName = outPath;
                                cpu.initialize();
                                cpu.loadGame(outPath);
                                op.initializeOpcodeMask();
                                grid.initialize();  



                                free(outPath);  // Libérez la mémoire allouée pour le chemin du fichier
                                break;
                            case NFD_CANCEL:
                                std::cout << "L'utilisateur a annulé la sélection." << std::endl;
                                break;
                            case NFD_ERROR:
                                std::cerr << "Erreur: " << NFD_GetError() << std::endl;
                                break;
                        }


                   }
                   if (ImGui::MenuItem("Save", "Ctrl+S")) {
                   }
                   if (ImGui::MenuItem("Save as..")) { 
                    }
             ImGui::EndMenu();
             }
             ImGui::EndMainMenuBar();
        }






//--------------------------------------------------



        ImGui::Render();
        //






        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        // Dessinez ici vos éléments de rendu avec SDL et ImGui




        grid.print(renderer);

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);

        SDL_RenderPresent(renderer);

        // Calculer le temps écoulé et faire une pause si nécessaire
        int frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    std::cout << "FIN DU PROGRAME" << std::endl;    


    Mix_CloseAudio();
    Mix_Quit();

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    exit(0);
}
