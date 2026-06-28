#include <windows.h>
#include <cstdio>
#include <MinHook.h>

uintptr_t base = (uintptr_t)GetModuleHandle(nullptr);

struct render_context;
struct user_input;
struct body;
struct cell;

struct real_2
{
    float x;
    float y;
};
struct real_3
{
    float x;
    float y;
    float z;
};
struct real_4
{
    float x;
    float y;
    float z;
    float w;
};
union material_t_u_76
{
    int tags;
};
struct material_t {
    int id;
    char *name;
    int next_variant;
    int tags;
    int tier;
    float drop_weight;
    int spawn_with[4];
    float base_cost;
    float random_cost;
    float genome_size;
    float growth_rate;
    float max_health;
    float transfer_rate;
    float regen;
    union material_t_u_76 field14_0x4c;
    float density;
    float sharpness;
    float leeching;
    float hardness;
    float max_radial_force;
    float max_angular_force;
    float radial_compliance;
    float angular_compliance;
    float plasticity;
    float friction;
    float restitution;
    float drag;
    float tangent_drag;
    float movement_force;
    float conductivity;
    float leak_conductivity;
    float capacitance;
    float inv_capacitance;
    float directional_conductivity;
    float heat_conductivity;
    float leak_heat_conductivity;
    float heat_capacity;
    float inv_heat_capacity;
    struct real_4 base_color;
    float light_radius;
    float light_intensity;
    struct real_3 emission;
    int texture_type;
    struct real_2 uv;
    int combine_material_index1;
    int combine_material_index2;
    void (*physics_update_fn)(struct cell *);
    void (*force_update_fn)(struct cell *);
    void (*electric_update_fn)(struct cell *);
    void (*connection_update_fn)(struct cell *);
    void (*brain_fn)(struct cell *);
    void (*destroyed_fn)(struct cell *);
};

using LogPrintfFn = int(*)(const char*);
LogPrintfFn logPrintf = nullptr;

using UpdateGameFn = void(*)(render_context*, render_context*, user_input*);
UpdateGameFn OriginalUpdateGame = nullptr;

void HookedUpdateGame(
render_context* rc1,
render_context* rc2,
user_input* input)
{


    OriginalUpdateGame(rc1, rc2, input);
}

using InitMaterialsListFn = void(*)();
InitMaterialsListFn OriginalInitMaterialsList = nullptr;
void HookedInitMaterialsList()
{
    OriginalInitMaterialsList();

    material_t *materials_list = reinterpret_cast<material_t(*)>(base + 0x1ed800); // i have no idea what im doing lmao
    material_t *pmVar49;
    pmVar49 = materials_list;
    int* n_materials = reinterpret_cast<int(*)>(base + 0x1ed808);
    int lVar137 = 81;//*n_materials;//(longlong)n_materials;
    n_materials = n_materials + 1;
    //memcpy();
    int uVar45 = 100;//str_to_id("FAST");
    pmVar49[lVar137].id = uVar45;
    pmVar49[lVar137].tags = 0x14;
    pmVar49[lVar137].tier = 0;
    pmVar49[lVar137].drop_weight = 0.5;
    pmVar49[lVar137].base_cost = 3.0;
    pmVar49[lVar137].genome_size = 4.0;
    pmVar49[lVar137].movement_force = pmVar49[lVar137].movement_force * 14.0;
    pmVar49[lVar137].base_color;

}

using GiveMutationFn = void(*)(body *,int ,int *,int ,bool );
GiveMutationFn OriginalGiveMutation = nullptr;

void HookedGiveMutation(body *param_1,int param_2,int *param_3,int param_4,bool param_5)
{
    //reinterpret_cast<void(*)()>(base + 0x6f7d0)(); // set lava walls
    OriginalGiveMutation(param_1,param_2,param_3,param_4,param_5);

    // putting this here so i can turn it on at will in the right context

    int n_materials = *reinterpret_cast<int(*)>(base + 0x1ed808);
    printf("%d\n", n_materials);

    material_t** materials_list = reinterpret_cast<material_t**>(base + 0x1ed800); // i have no idea what im doing lmao
    int cell_type_index = n_materials + 1;
    (*materials_list)[cell_type_index] = (*materials_list)[1];
    (*materials_list)[cell_type_index].base_cost = 43.f;
    (*materials_list)[cell_type_index].movement_force = 0.5f;
    (*materials_list)[cell_type_index].base_color = real_4(1., 0.5, 1., 1.);
}

using MapGenFn = void(*)();
MapGenFn OriginalMapGen = nullptr;
void HookedMapGen()
{
    OriginalMapGen();
}

DWORD WINAPI MainThread(LPVOID)
{
    AllocConsole();

    FILE* file;
    freopen_s(&file, "CONOUT$", "w", stdout);

    printf("Hello from the injected DLL!\n");

    logPrintf = reinterpret_cast<LogPrintfFn>(base + 0x218C0);
    logPrintf("LOG WORKS :D");

    if (MH_Initialize() != MH_OK)
    {
        printf("MinHook init failed\n");
        return 0;
    }

    printf("MinHook initialized\n");

    void* target = (void*)(base + 0x143db0);

    MH_Initialize();

    MH_CreateHook(
        target,
        reinterpret_cast<LPVOID>(HookedUpdateGame),
        reinterpret_cast<void**>(&OriginalUpdateGame));

    MH_EnableHook(target);

    target = (void*)(base + 0x6fc80);

    MH_CreateHook(
        target,
        reinterpret_cast<LPVOID>(HookedGiveMutation),
        reinterpret_cast<void**>(&OriginalGiveMutation));

    MH_EnableHook(target);


    target = (void*)(base + 0x106a10);

    MH_CreateHook(
        target,
        reinterpret_cast<LPVOID>(HookedMapGen),
        reinterpret_cast<void**>(&OriginalMapGen));

    MH_EnableHook(target);

    // target = (void*)(base + 0x11f560);
    //
    // MH_CreateHook(
    //     target,
    //     &HookedInitMaterialsList,
    //     reinterpret_cast<void**>(&OriginalInitMaterialsList));
    //
    // MH_EnableHook(target);

    while (true)
    {
        Sleep(1000);
    }

    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE module,
    DWORD reason,
    LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(module);

        CreateThread(
            nullptr,
            0,
            MainThread,
            nullptr,
            0,
            nullptr);
    }

    return TRUE;
}