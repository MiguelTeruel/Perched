#include "game.hpp"

// auto&& deduce referencia a rvalue o a lvalue
auto timedCall = [](std::string_view name, auto &&func)
{
    GameTimer_t timerc;
    func();
    std::cout << "[" << name << "]" << timerc.ellapsed() << " ";
};

void GameManager_t::createActionsIA()
{

    // Acciones del Aguila, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Aguila, -10, 3, 1, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Aguila, 3, -10, 2, 1));
    // Hacer nido
    action_container.emplace_back(Action_t(type_enemy::Aguila, 1, 2, -10, 3));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Aguila, 3, 2, 1, -10));

    // Acciones de la Cabra, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Cabra, -10, 4, 0, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Cabra, 4, -10, 0, 2));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Cabra, 4, 2, 0, -10));

    // Acciones de la Araña, valores(tipo, atacar, comer, hacer nido, proteger ):
    // Atacar
    action_container.emplace_back(Action_t(type_enemy::Aranya, -10, 4, 0, 2));
    // Comer
    action_container.emplace_back(Action_t(type_enemy::Aranya, 4, -10, 0, 2));
    // Proteger
    action_container.emplace_back(Action_t(type_enemy::Aranya, 4, 2, 0, -10));
}

void GameManager_t::createBT(BehaviourTree_t *tree)
{
    createActionsIA();
    tree->createNode<BTNodeSelector_t>(
        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Cabra),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    // Create ROCA
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    // Create ROCA
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 30.0),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()
                    // Create ROCA
                    ),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5)),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Cabra, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BTSeekOneAxis_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()))),

        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Aranya),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BT_ACT_seek_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BTThrowObject_t>(objects_type::Telaranya),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aranya, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(50.0, 0.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BT_Change_Target_From_Init>(50.0, -50.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BT_Change_Target_From_Init>(0.0, -50.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>(),

                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>()))),

        //        &tree->createNode<BTNodeSequence_t>(
        //            &tree->createNode<BTCheckType_t>(type_enemy::Aranya),
        //            &tree->createNode<BT_Check_See_Player_t>(),
        //            &tree->createNode<BT_ACT_seek_t>(),
        //            &tree->createNode<BTResetWait_t>(),
        //            &tree->createNode<BT_Change_Target_From_Init>(0.0 , -50.0),
        //            &tree->createNode<BT_ACT_arrive_t>()
        //            //&tree->createNode<BTThrowObject_t>(objects_type::Telaranya)
        //        ),
        &tree->createNode<BTNodeSequence_t>(
            &tree->createNode<BTCheckType_t>(type_enemy::Aguila),
            &tree->createNode<BTChooseAction_t>(&action_container),
            &tree->createNode<BTNodeSelector_t>(
                // Rama Atacar
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Attack), // Atacar
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Check_See_Player_t>(),
                    &tree->createNode<BT_ACT_seek_t>(),
                    &tree->createNode<BTResetWait_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Atacar, 2),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Comer
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Eat), // Comer
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BTSearchTarget_t>(objects_type::Arbusto),
                    &tree->createNode<BT_ACT_arrive_t>(),
                    &tree->createNode<BT_Do_Action_t>(type_action::Comer, 5),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Hacer_Nido
                // NO IMPLEMENTADA
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Make_nido), // Hacer nido
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(50.0, 0.0),
                    &tree->createNode<BT_ACT_arrive_t>()),

                // Rama Proteger
                &tree->createNode<BTNodeSequence_t>(
                    &tree->createNode<BTCheck_Action_t>(type_enemy::Aguila, goal_types::Protect), // Proteger
                    &tree->createNode<BT_Apply_Goal_t>(),
                    &tree->createNode<BT_Change_Target_From_Init>(0.0, 0.0),
                    &tree->createNode<BT_Do_Action_t>(type_action::Vigilar, 5),
                    &tree->createNode<BT_ACT_arrive_t>()))));
}

void GameManager_t::createLevel1()
{
    GOFact.crearRocas(3);

    Collision.sizeMapa(-100, 1000, -1500, 1500);

    this->createBT(&tree1);

    GOFact.loadLevelJSON("assets/levels/Mundo1/level1.json", &tree1);

    PathP.ponerSalientes(75, 45, EntityMan.getBlackBoard().salientes_bb);

    // le paso al spawner la funcion que quiero que haga cuando spawnee
    /*auto& sp = GOFact.createSpawner(200, 1,
        [&](const SpawnerComponent_t& sp) {
            //getRequiredComponent devuelve un componente a partir de otro
            const auto* phy = EntityMan.getRequiredComponent<SpawnerComponent_t, PhysicsComponent_t>(sp);
            if (!phy) { return; }
            auto& e = GOFact.createRoca(phy->x, phy->y, 1, Render.getMotor());
        }
    );*/

    std::vector<TextHijo_t> textos;
    textos.reserve(5);
    TextHijo_t vidas = {"Vidas : ", -1};
    textos.emplace_back(vidas);
    TextHijo_t puntos = {"Puntos : ", 0};
    textos.emplace_back(puntos);
    TextHijo_t control = {"Control : ", -1};
    textos.emplace_back(control);
    TextHijo_t stamina = {"Stamina : ", 0};
    textos.emplace_back(stamina);

    GOFact.createText("HUD", textos, 50, 50, 500, 500);

    Physics.calculozinicio(EntityMan);

    Casilla a;
    a.x = 23;
    a.y = 0;
    conejilloindias1 = GOFact.createRoca(a.x * 20, a.y * 20, 0, false).getEntityID();

    
    Casilla b;
    b.x = 26;
    b.y = 18;

    //posis = PathA.aStar(a, b, EntityMan.getBlackBoard().salientes_bb);

    //Probar navmesh
    //PathA.checkStartingTriangle(EntityMan.getBlackBoard().navMesh, Vector3d(0,0,0));

    Casilla ini;
    ini.x = 16;
    ini.y = 9;

    conejilloindias = GOFact.createRoca(ini.x * 20, ini.y * 20, 0, false).getEntityID();

    Casilla fin;
    fin.x = 20;
    fin.y = 0;

//    ruta = PathP.buscar(ini.x, ini.y, fin.x, fin.y);
//
//    if (ruta.size() > 0)
//    {
//        ruta.push_back(fin);
//    }
}