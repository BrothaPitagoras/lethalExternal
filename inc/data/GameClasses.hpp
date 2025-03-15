#pragma once

#include <includes.h>

namespace Offsets {

    inline uintptr_t singleton_network_class = 0x5844118;
    inline uintptr_t network_static_fields_offset = 0xB8;
    inline uintptr_t network_object_offset = 0x00;


    struct Network_PlayerSpot_o // sizeof=0xA8
    {                          // XREF: Network_PlayerSpot_o/r
        char pad_0000[0x10];                                        //0x00
        bool playerReady;                                           //0x10
        char pad_0011[0x03];
        int32_t _playerCharacterIndex;                              //0x14
        struct Photon_Realtime_Player_o* photonPlayer;              //0x18
        struct System_String_o* unityPlayerID;                      //0x20
        int32_t experience;                                         //0x28
        int32_t level;                                              //0x2C
        int32_t prestige;                                           //0x30
        char pad_0035[4];
        struct Player_o* player;                                    //0x38
        float playerVolume;                                         //0x40
        char pad_0045[4];                                           
        struct System_String_o* accountName;                        //0x48
        bool isKicked;                                              //0x50
        bool isHacker;                                              //0x51
        bool isBlocked;                                             //0x52
        char pad_0053[5];
        struct RoleType_array* roleBadges;                          //0x58
        int32_t role;                                               //0x60
        int32_t prestigeIndex;                                      //0x64
        bool prestigeTheme;                                         //0x68
        char pad_0069[7];
        struct Contract_o* votedContract;                           //0x70
        int32_t platformType;                                       //0x78
        bool hasReceivedPlayerInformation;                          //0x7C
        bool playerIsBlocked;                                       //0x7D
        char pad_007E[2];
        int32_t legacyLevel;                                        //0x80
        int32_t legacyAccent;                                       //0x84
        int32_t legacyBackground;                                   //0x88
        int32_t legacyColour;                                       //0x8C
        struct List_PlayerEquipment_o* playerEquipment;             //0x90
        bool hasBroughtItems;                                       //0x98
        char pad_0099[3];
        int32_t totalEquipmentCost;                                 //0x9C
        struct System_Action_o* onBlockMuteStateChanged;            //0xA0
    };

    struct Network_PlayerSpot_array
    {
        char pad_0000[0x18];                        //0x00
        uint64_t count;                             //0x18
        Network_PlayerSpot_o playerSpots[4];        //0x20    //this might be fked due to size if error come back here TODO
    };

    struct List_Network_PlayerSpot_o
    {
        char pad_0000[0x10];
        Network_PlayerSpot_array* _items;
    };

    struct Network_o //sizeof=0xE8
    {
        char pad_0000[0x28];                                                        //0x00
        Player_o* localPlayer;												        //0x28
        List_Network_PlayerSpot_o* playersData;                                     //0x30
        struct UnityEngine_Color_array* playerColors;                               //0x38
        struct UnityEngine_Color_array* defaultPlayerColors;                        //0x40
        struct UnityEngine_Events_UnityEvent_o* JoinedLobby;                        //0x48
        struct UnityEngine_Events_UnityEvent_o* JoinedRoom;                         //0x50
        struct UnityEngine_Events_UnityEvent_o* LeftRoom;                           //0x58
        struct UnityEngine_Events_UnityEvent_o* Disconnected;                       //0x60
        struct Network_MicrophoneEvent_o* OnMicrophoneChanged;                      //0x68
        struct Network_NetworkEvent_o* OnMasterClientSwitchedEvent;                 //0x70
        struct Network_NetworkEvent_o* OnPlayerEnteredRoomEvent;                    //0x78
        struct Network_NetworkEvent_o* OnPlayerLeftRoomEvent;                       //0x80
        struct Network_NetworkEvent_o* OnPlayerSpotAssigned;                        //0x88
        struct UnityEngine_Events_UnityEvent_o* OnLocalPlayerSpawned;               //0x90
        struct UnityEngine_Events_UnityEvent_o* OnSeasonalEventCompleted;           //0x98
        struct UnityEngine_Events_UnityEvent_Color__int__o* OnPlayerColorChanged;   //0xA0
        struct Lavender_Progression_LevelSystem_o* m_levelSystem;                   //0xA8
        bool isChangingScenes;                                                      //0xB0
        char pad_00B9[7];                                                           
        struct System_String_o* lastOnlineRoomName;                                 //0xB8
        struct System_Collections_Generic_HashSet_string__o* recentKickedFromRooms; //0xC0
        bool failedToConnectToVivox;                                                //0xC8
        bool isAttemptingVivoxLogin;                                                //0xC9
        char pad_00CA[6];
        struct Network_InviteSystem_o* inviteSystem;                                //0xD0
        bool isChangingRegion;                                                      //0xD8
        char pad_00D9[7];
        struct System_String_o* changeToRegionOnDisconnect;                         //0xE0
    };



    struct Player_o {
        char pad_0000[0x20];                                                                    //0x00
        struct Photon_Pun_PhotonView_o* view;                                                   //0x20
        bool isDead;                                                                            //0x28
        bool isDyingLocally;                                                                    //0x29
        char pad_002A[2];
        int32_t modelID;                                                                        //0x2C
        struct PlayerCharacter_o* playerCharacter;                                              //0x30
        struct ClosetZone_o* closet;                                                            //0x38
        struct UnityEngine_GameObject_o* headObject;                                            //0x40
        struct UnityEngine_Transform_o* trackedHead;                                            //0x48
        struct System_Collections_Generic_List_KeyInfo__o* keys;                                //0x50
        struct UnityEngine_Camera_o* cam;                                                       //0x58
        struct LevelRoom_o* currentRoom;                                                        //0x60
        struct UnityEngine_Transform_o* mapIcon;                                                //0x68
        struct PhotonObjectInteract_o* rightCurrentHeldObject;                                  //0x70
        struct PhotonObjectInteract_o* leftCurrentHeldObject;                                   //0x78
        struct UnityEngine_GameObject_array* characterModels;                                   //0x80
        struct UnityEngine_GameObject_o* ghostDeathHands;                                       //0x88
        char pad_0090[8];                                                                       //0x90
        struct HeadMountedSocket_o* headSocket;                                                 //0x98
        struct UnityEngine_Transform_o* aiTargetPoint;                                          //0xA0
        struct UnityEngine_Transform_o* huntingTargetPoint;                                     //0xA8
        struct UnityEngine_GameObject_o* deadBodyPrefab;                                        //0xB0
        struct DeadPlayer_o* deadPlayer;                                                        //0xB8
        struct PlayerSanity_o* playerSanity;                                                    //0xC0
        struct PlayerStats_o* playerStats;                                                      //0xC8
        struct FootstepController_o* footstepController;                                        //0xD0
        struct JournalController_o* journalController;                                          //0xD8
        struct UnityEngine_Renderer_array* allRends;                                            //0xE0
        bool isSafeGhostCursed;                                                                 //0xE8
        char pad_00E9[7];
        struct PlayerAudio_o* playerAudio;                                                      //0xF0
        struct PlayerGraphics_o* playerGraphics;                                                //0xF8
        struct PlayerStamina_o* stamina;                                                        //0x100
        float movementSpeed;                                                                    //0x108
        bool monkeyPawLeaveEffectIsActive;                                                      //0x10C
        char pad_010D[3];
        struct PhysicsCharacterController_o* charController;                                    //0x110
        struct UnityEngine_AudioListener_o* listener;                                           //0x118
        struct FirstPersonController_o* firstPersonController;                                  //0x120
        struct PCPropGrab_o* pcPropGrab;                                                        //0x128
        struct DragRigidbodyUse_o* dragRigidBodyUse;                                            //0x130
        struct PCCanvas_o* pcCanvas;                                                            //0x138
        struct PCCrouch_o* pcCrouch;                                                            //0x140
        struct PCMenu_o* pcMenu;                                                                //0x148
        struct PCControls_o* pcControls;                                                        //0x150
        struct PCFlashlight_o* pcFlashlight;                                                    //0x158
        struct UnityEngine_Animator_o* charAnim;                                                //0x160
        struct UnityEngine_InputSystem_PlayerInput_o* playerInput;                              //0x168
        struct PCItemSway_o* itemSway;                                                          //0x170
        struct PCItemSway_o* lightSway;                                                         //0x178
        struct UnityEngine_Transform_o* deadPlayerSpawnPoint;                                   //0x180
        struct UnityEngine_XR_Interaction_Toolkit_XRBaseInteractor_o* leftHandInteractor;       //0x188
        struct UnityEngine_XR_Interaction_Toolkit_XRBaseInteractor_o* rightHandInteractor;      //0x190
        struct UnityEngine_Transform_o* xrOrigin;                                               //0x198
        struct VRMovementSettings_o* movementSettings;                                          //0x1A0
        struct VRBelt_o* vrBelt;                                                                //0x1A8
        struct UnityEngine_XR_Interaction_Toolkit_XRSocketInteractor_o* leftVRBeltDropZone;     //0x1B0
        struct UnityEngine_XR_Interaction_Toolkit_XRSocketInteractor_o* rightVRBeltDropZone;    //0x1B8
        struct TrailerCamera_o* trailerCamera;                                                  //0x1C0
        struct VRLoading_o* vrLoading;                                                          //0x1C8
    };
}