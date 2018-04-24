#include "CDelaunay.h"
#include <gtest/gtest.h>
#include "SDL.h"
#include <time.h>
#include <conio.h>
#define  SCALE 45
int main(int argc, char* argv[])
{
  CDelaunay Test;


  std::vector<sPoint> myVector = Test.fillPoints(20);


  myVector = Test.bubbleSort(myVector, myVector.size());


  std::cout << "myvector contains:";
  Test.partitionPoints();
  for (int i = 0; i < myVector.size(); i++)
  {
    std::cout << ' ' << myVector[i].x << "," << myVector[i].y << ' ';
  }
  std::cout << '\n';
  std::cout << Test.m_SubsetList.size();

//  _getch();
  if (SDL_Init(SDL_INIT_VIDEO) == 0) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    if (SDL_CreateWindowAndRenderer(1080, 720, 0, &window, &renderer) == 0) {
      SDL_bool done = SDL_FALSE;
      SDL_bool first = SDL_FALSE;


      while (!done) {
        SDL_Event event;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
       // SDL_RenderSetScale(renderer,1.5, 1.5);
        while (!first)
        {
         
         
          SDL_RenderPresent(renderer);
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
          for (int i = 0; i < Test.m_vEdges.size(); i++)
          {
           
              SDL_RenderDrawLine(renderer,Test.m_vEdges[i].a.x * SCALE, Test.m_vEdges[i].a.y * SCALE, Test.m_vEdges[i].b.x * SCALE, Test.m_vEdges[i].b.y * SCALE);
              SDL_RenderPresent(renderer);
          }
          for (int i = 0; i < Test.m_vPointLists.size(); i++)
          {
           
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawPoint(renderer, Test.m_vPointLists[i].x*SCALE, Test.m_vPointLists[i].y*SCALE);
          }
         // SDL_RenderPresent(renderer);
          SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
          for (int i = 0; i < Test.m_vSubsetNearEdges.size(); i++)
          {

            SDL_RenderDrawLine(renderer, Test.m_vSubsetNearEdges[i].a.x * SCALE, Test.m_vSubsetNearEdges[i].a.y * SCALE, Test.m_vSubsetNearEdges[i].b.x * SCALE, Test.m_vSubsetNearEdges[i].b.y * SCALE);
          //  SDL_RenderPresent(renderer);
          }
          
     
          SDL_RenderPresent(renderer);
          first = SDL_TRUE;
        }
        SDL_RenderClear(renderer);




        while (SDL_PollEvent(&event)) {
          if (event.type == SDL_QUIT) {
            done = SDL_TRUE;
          }
        }
      }
    }

    if (renderer) {
      SDL_DestroyRenderer(renderer);
    }
    if (window) {
      SDL_DestroyWindow(window);
    }
  }
  SDL_Quit();
  return 0;

 
}
