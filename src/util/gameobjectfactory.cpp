#include "gameobjectfactory.hpp"


ECS::Entity_t& GameObjectFactory_t::createEntity(int32_t x, int32_t y, const std::string_view filename) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    m_EntMan.addComponent<HealthComponent_t>(e);

    //re.loadFromFile(filename);

    ph.x = x;
    ph.y = y;
    ph.z = 15;

    return e;
}

/****************************************************************************************************/
/*******************************************PLAYER***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createPlayer(const picojson::array &player) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = player.at(0).get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    ph.roty = 180;

    auto& he = m_EntMan.addComponent<HealthComponent_t>(e);
    const picojson::value health = player.at(0).get("health");
    he.health = std::stoi(health.get("health").to_str());
    he.maxHealth = std::stoi(health.get("maxHealth").to_str());


    auto& est = m_EntMan.addComponent<StaminaComponent_t>(e);
    const picojson::value stamina = player.at(0).get("stamina");
    est.maxStamina = std::stoi(stamina.get("maxStamina").to_str());
    est.cantStamina = std::stoi(stamina.get("cantStamina").to_str());

    const picojson::value render = player.at(0).get("render");
    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo, false);
    re.w = re.h = re.d = std::stof(render.get("size").to_str());
    
    //re.entityNodes.node.node->setScale(Vector3d(3, 3, 3));
    
    float sizeb = std::stof(render.get("sizebrazo").to_str());
    float sizec = std::stof(render.get("sizecabeza").to_str());

    float disxbrazoI = std::stof(render.get("disxbrazoI").to_str());
    float disybrazoI = std::stof(render.get("disybrazoI").to_str());
    float diszbrazoI = std::stof(render.get("diszbrazoI").to_str());

    float disxbrazoD = std::stof(render.get("disxbrazoD").to_str());
    float disybrazoD = std::stof(render.get("disybrazoD").to_str());
    float diszbrazoD = std::stof(render.get("diszbrazoD").to_str());

    float disxpiernaI = std::stof(render.get("disxpiernaI").to_str());
    float disypiernaI = std::stof(render.get("disypiernaI").to_str());
    float diszpiernaI = std::stof(render.get("diszpiernaI").to_str());

    float disxpiernaD = std::stof(render.get("disxpiernaD").to_str());
    float disypiernaD = std::stof(render.get("disypiernaD").to_str());
    float diszpiernaD = std::stof(render.get("diszpiernaD").to_str());

    float distanciaxcabeza = std::stof(render.get("distanciaxcabeza").to_str());
    float distanciaycabeza = std::stof(render.get("distanciaycabeza").to_str());
    float distanciazcabeza = std::stof(render.get("distanciazcabeza").to_str());

  /*  re.entityNodes.childs = {
        {motor->createCubeNode(sizebrazo), ph.x + disxbrazoD, ph.y + disybrazoD, ph.z, "brazo derecho", disxbrazoD, disybrazoD, diszbrazoD},
        {motor->createCubeNode(sizebrazo), ph.x + disxbrazoI, ph.y + disybrazoI, ph.z, "brazo izquierdo", disxbrazoI, disybrazoI, diszbrazoI},
        {motor->createCubeNode(sizebrazo), ph.x + disxpiernaD, ph.y + disypiernaD, ph.z, "pierna derecha", disxpiernaD, disypiernaD, diszpiernaD},
        {motor->createCubeNode(sizebrazo), ph.x + disxpiernaI, ph.y + disypiernaI, ph.z, "pierna izquierda", disxpiernaI, disypiernaI, diszpiernaI},
        {motor->createCubeNode(sizecabeza), ph.x + distanciaxcabeza, ph.y + distanciaycabeza, ph.z, "cabeza", distanciaxcabeza, distanciaycabeza, distanciazcabeza}
    }; */


    auto& in = m_EntMan.addComponent<InputComponent_t>(e);
    const picojson::value input = player.at(0).get("input");

    float disx1BraD = std::stof(input.get("disx1BraD").to_str());
    float disx2BraD = std::stof(input.get("disx2BraD").to_str());
    float disy1BraD = std::stof(input.get("disy1BraD").to_str());
    float disy2BraD = std::stof(input.get("disy2BraD").to_str());
    float disy3BraD = std::stof(input.get("disy3BraD").to_str());
    float disy4BraD = std::stof(input.get("disy4BraD").to_str());

    in.distsBrazoD = { disx1BraD, disx2BraD, disy1BraD, disy2BraD, disy3BraD, disy4BraD };

    float disx1BraI = std::stof(input.get("disx1BraI").to_str());
    float disx2BraI = std::stof(input.get("disx2BraI").to_str());
    float disy1BraI = std::stof(input.get("disy1BraI").to_str());
    float disy2BraI = std::stof(input.get("disy2BraI").to_str());
    float disy3BraI = std::stof(input.get("disy3BraI").to_str());
    float disy4BraI = std::stof(input.get("disy4BraI").to_str());

    in.distsBrazoI = { disx1BraI, disx2BraI, disy1BraI, disy2BraI, disy3BraI, disy4BraI };

    float disx1PieD = std::stof(input.get("disx1PieD").to_str());
    float disx2PieD = std::stof(input.get("disx2PieD").to_str());
    float disy1PieD = std::stof(input.get("disy1PieD").to_str());
    float disy2PieD = std::stof(input.get("disy2PieD").to_str());
    float disy3PieD = std::stof(input.get("disy3PieD").to_str());

    in.distsPiernaD = { disx1PieD, disx2PieD, disy1PieD, disy2PieD, disy3PieD };

    float disx1PieI = std::stof(input.get("disx1PieI").to_str());
    float disx2PieI = std::stof(input.get("disx2PieI").to_str());
    float disy1PieI = std::stof(input.get("disy1PieI").to_str());
    float disy2PieI = std::stof(input.get("disy2PieI").to_str());
    float disy3PieI = std::stof(input.get("disy3PieI").to_str());

    in.distsPiernaI = { disx1PieI, disx2PieI, disy1PieI, disy2PieI, disy3PieI};

    float disyCab   = std::stof(input.get("disyCab").to_str());
    float disxCabDL = std::stof(input.get("disxCabDL").to_str());
    float disxCabDR = std::stof(input.get("disxCabDR").to_str());
    float disxCabU  = std::stof(input.get("disxCabU").to_str());
    float disxCabUL = std::stof(input.get("disxCabUL").to_str());
    float disxCabUR = std::stof(input.get("disxCabUR").to_str());

    in.distsCabeza = { disyCab, disxCabDL, disxCabDR, disxCabU, disxCabUL, disxCabUR};


    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.properties = ColliderComponent_t::P_IsPlayer;

    co.boxes = {
        { -re.w/2,  re.w/2,  -re.h/2,  re.h/2,  -re.d/2,  re.d/2, false, 0, 0, false}, //cuerpo
        {-sizec*2, sizec*2, -sizec*2, sizec*2, -sizec*2, sizec*2, false, distanciaxcabeza, distanciaycabeza, false}, //cabeza
        {-sizeb*2, sizeb*2, -sizeb*2, sizeb*2, -sizeb*2, sizeb*2, false, disxbrazoI, disybrazoI, false}, //brazo izquierdo
        {-sizeb*2, sizeb*2, -sizeb*2, sizeb*2, -sizeb*2, sizeb*2, false, disxbrazoD, disybrazoD, false}, //brazo derecho
        {-sizeb*2, sizeb*2, -sizeb*2, sizeb*2, -sizeb*2, sizeb*2, false, disxpiernaI, disypiernaI, false}, //pierna izquierdo
        {-sizeb*2, sizeb*2, -sizeb*2, sizeb*2, -sizeb*2, sizeb*2, false, disxpiernaD, disypiernaD, false}, //pierna derecho
    };

    
    m_EntMan.addComponent<ControlComponent_t>(e);
    m_EntMan.addComponent<PuntosComponent_t>(e);

    auto& so = m_EntMan.addComponent<SoundComponent_t>(e);
    so.event_id = "event:/Prueba4";
    so.marked_for_init = 1;

    m_EntMan.getBlackBoard().playerID = e.getEntityID();

    return e;
}

void setComponenteVision(auto* co, float negw, float posw, float negh, float posh, float negd, float posd){
    if (co) {
        co->boxes = {{-negw, posw, -negh, posh, -negd, posd}};
        co->properties = ColliderComponent_t::P_EnemyVisual;
    }  
}

ECS::Entity_t& GameObjectFactory_t::createEnemy(const picojson::value &enemy, BehaviourTree_t * tree) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = enemy.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& he = m_EntMan.addComponent<HealthComponent_t>(e);
    const picojson::value health = enemy.get("health");
    he.health = std::stoi(health.get("health").to_str());
    he.maxHealth = std::stoi(health.get("maxHealth").to_str());
    he.damageInflicted = std::stoi(health.get("damageInflicted").to_str());
    he.selfDamageOnInfliction = std::stoi(health.get("selfDamageOnInfliction").to_str());

    auto& coVisual = m_EntMan.addComponentVisual<ColliderComponent_t>(e);
    const picojson::value vision = enemy.get("vision");
    auto xneg = std::stof(vision.get("xneg").to_str());
    auto xpos = std::stof(vision.get("xpos").to_str());
    auto yneg = std::stof(vision.get("yneg").to_str());
    auto ypos = std::stof(vision.get("ypos").to_str());
    auto zneg = std::stof(vision.get("zneg").to_str());
    auto zpos = std::stof(vision.get("zpos").to_str());
    setComponenteVision(&coVisual, xneg, xpos, yneg, ypos, zneg, zpos);


    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = enemy.get("render");

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Enemy;

    auto& ia = m_EntMan.addComponent<IAComponent_t>(e);
    const picojson::value ias = enemy.get("ia");

    if (ias.get("type").to_str() == "cabra") {
        ia.enemy = type_enemy::Cabra;
    } else if (ias.get("type").to_str() == "aranya") {
        ia.enemy = type_enemy::Aranya;
    } else if (ias.get("type").to_str() == "aguila") {
        ia.enemy = type_enemy::Aguila;
    }

    ia.ix = ph.x;
    ia.iy = ph.y;
    ia.arrivalRadius = std::stod(ias.get("arrivalRadius").to_str());
    ia.tree = tree;
    ia.cansancio = std::stod(ias.get("cansancio").to_str());
    ia.ira = std::stod(ias.get("ira").to_str());
    ia.stamina = std::stod(ias.get("stamina").to_str());

    return e;
}

void GameObjectFactory_t::crearEnemigos (BehaviourTree_t* tree1, const picojson::array &enemies) const {
    for (int i=0; i < enemies.size(); i++) {
        createEnemy(enemies.at(i), tree1);
    }   
    //createEnemy(420, 300,type_enemy::Cabra, tree1);
    //createEnemy(220, 230 ,type_enemy::Aranya, tree1);
    //createEnemy(740, 580,type_enemy::Cabra, tree1);
    //createEnemy(220, 820,type_enemy::Aguila, tree1);
}

ECS::Entity_t& GameObjectFactory_t::createTelaranya(int32_t x, int32_t y, int32_t vel) const {
    auto& e = createEntity(x, y, "assets/telaranya.png");
    auto* phy = e.getComponent<PhysicsComponent_t>();
    auto* co = e.getComponent<ColliderComponent_t>();
    auto* he = e.getComponent<HealthComponent_t>();
    auto* re = e.getComponent<RenderComponent_t>();
    if (!re) { return e; }
    
    //auto tela = std::unique_ptr<Texture>(motor->getTexture("assets/textures/telaranya.png"));
    //re->entityNodes.node.node = motor->createCubeNode(5.0);
    //re->entityNodes.node.node->setMaterialTexture(tela.get());
    //re->w = re->h = re->d = re->entityNodes.node.node->getSize();

    if (phy) {
        phy->vy = 0;
        phy->z = 15;
        phy->vx = vel;
        //phy->gravity = 0;
    }
    
    if (co) {
    //    co->boxRoot.collided = false;
        co->boxes = {{-re->w/2, re->w/2, -re->h/2, re->h/2, -re->d/2, re->d/2}};
        co->properties = ColliderComponent_t::P_Telaranya;
    }    
    if (he) {
        he->damageInflicted = 0;
        he->selfDamageOnInfliction = 0;
        he->health = 3;
    }
    return e;
}

void GameObjectFactory_t::unfollowPalo(ECS::EntityID_t Entounfollow) const{
    for(auto follow : m_EntMan.template getComponents<FollowComponent_t>()){
        if(follow.followEntityID == Entounfollow){
            auto* phy = m_EntMan.getRequiredComponent<FollowComponent_t,PhysicsComponent_t>(follow);
            phy->vy = -2;
            m_EntMan.getStorageComponents().deleteComponentByTypeIDAndEntityID(follow.getComponentTypeID(),follow.getEntityID());
        }
    }
}

ECS::Entity_t& GameObjectFactory_t::createPalo(int32_t x, int32_t y, int32_t vel, ECS::EntityID_t Entfollow) const {
    auto& e = createEntity(x, y, "assets/palo.png");
    auto* phy = e.getComponent<PhysicsComponent_t>();
    auto* co = e.getComponent<ColliderComponent_t>();
    auto* he = e.getComponent<HealthComponent_t>();
    auto* re = e.getComponent<RenderComponent_t>();
    auto& fo = m_EntMan.addComponent<FollowComponent_t>(e);
    fo.x = 0;
    fo.y = 20;
    fo.z = 0;
    fo.followEntityID = Entfollow;

    if (!re) { return e; }

    //auto palo = std::unique_ptr<Texture>(motor->getTexture("assets/textures/palo.png"));
    //re->entityNodes.node.node = motor->createCubeNode(5.0);
    //re->entityNodes.node.node->setMaterialTexture(palo.get());
    //re->w = re->h = re->d = re->entityNodes.node.node->getSize();

    if (phy) {
        phy->vx = 0;
        phy->vy = 0;
        phy->z = 15;
        //phy->vy = -vel;
        //phy->gravity = 0;
    }
    
    if (co) {
        // co->boxRoot.box = {-re->w/2, re->w/2, -re->h/2, re->h/2, -re->d/2, re->d/2}; //cambiar
        // co->properties = ColliderComponent_t::P_Damages | ColliderComponent_t::P_IsSolid;
    }    
    if (he) {
        he->damageInflicted = 1;
        he->selfDamageOnInfliction = 1;
        he->health = 1;
    } 
    //Agregar al Blackboard
    //m_EntMan.getSingletonComponent<BlackboardComponent_t>().palos_bb.emplace_back(e);

    return e;
}

/****************************************************************************************************/
/********************************************META****************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createMeta(const picojson::array &meta) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = meta.at(0).get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = meta.at(0).get("collider");

    float w = std::stof(collider.get("w").to_str());
    float h = std::stof(collider.get("h").to_str());
    float d = std::stof(collider.get("d").to_str());

    co.boxes = {{-w/2, w/2, -h/2, h/2, -d/2, d/2}};
    co.properties = ColliderComponent_t::P_Meta;

    auto& so = m_EntMan.addComponent<SoundComponent_t>(e);
    so.event_id = "event:/Prueba5";
    so.isEvent3D = true;
    so.marked_for_init = 1;
    so.marked_for_play = 1;

    return e;
}

/****************************************************************************************************/
/********************************************CAMARA**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createCamera(int32_t x, int32_t y, uint32_t w, uint32_t h, ECS::EntityID_t followEID) const {
    auto& e = m_EntMan.createEntity();

    auto& cam = m_EntMan.addComponent<CameraComponent_t>(e);
    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);

    cam.camNode = motor->getCamera();

    //ph.gravity = 0;

    cam.srcx = x;
    cam.srcy = y;
    cam.w = w;
    cam.h = h;
    cam.followEntityID = followEID;

    return e;
}

/****************************************************************************************************/
/*********************************************ROCA***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createRoca(int32_t x, int32_t y, int32_t vel, bool mover) const {
    auto& e = createEntity(x, y, "assets/pajaro.png");
    //std::cout << "Roca: " << e.getEntityID() << "\n";

    auto* phy = e.getComponent<PhysicsComponent_t>();
    auto* co = e.getComponent<ColliderComponent_t>();
    auto* he = e.getComponent<HealthComponent_t>();

    auto* re = e.getComponent<RenderComponent_t>();

    if (!re) { return e; }

    re->entityNodes.node.node = motor->createMeshNode("assets/modelados/roqui/roqui.obj", false);
    
    //re->w = re->h = re->d = re->entityNodes.node.node->getSize();

    if (phy) {
        phy->vx = 0;
        phy->vy = 0;
        phy->z = 15;
    }
    
    if (co) {
        co->boxes = {{-re->w/2, re->w/2, -re->h/2, re->h/2, -re->d/2, re->d/2}};
        co->properties = ColliderComponent_t::P_Damages;
        co->nomover = mover;
    }    

    if (he) {
        he->damageInflicted = 1;
        he->selfDamageOnInfliction = 1;
        he->health = 1;
    }

    return e;
}

void GameObjectFactory_t::crearRocas (uint32_t cant) const {
    float x = rand() % 800 + 1;
    float y = 0;
    int velo=1;

    int xx = 20;
           
    for(auto j=0; j<cant; ++j){
        //x = rand() % 800 + 1;
        //y = 800+rand()%(5000-800);
        x = (((j*2)+14)*xx)+420;
        y = 440;
        velo = 2+rand()%(7-2);
        auto& enti =  createRoca(x, y, velo, true);
        
       // auto linerock = motor->drawA3DLine(x, y, 15, 180); //x,y,z,rotation
    }
}

/****************************************************************************************************/
/*****************************************SALIENTES**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createSaliente(const picojson::value &saliente) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = saliente.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = std::stoi(fisica.get("roty").to_str());
    ph.friction = 0.85f;

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = saliente.get("render");

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);
    //re.entityNodes.node.node->setScale(Vector3d(4, 4, 4));

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = saliente.get("collider");
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());

    int numboxes = 0;

    if (saliente.get("partes").to_str() != "null") {
        while (saliente.get("partes").get(numboxes).to_str() != "null") {
            numboxes++;
        }
    }

    co.boxes.reserve(numboxes);

    //std::cout << "NumboxesI:" << numboxes << "\n";

    if (numboxes > 0 && saliente.get("partes").to_str() != "null") {
        int i = 0;

        while (saliente.get("partes").get(i).to_str() != "null") {
            float w = std::stof(saliente.get("partes").get(i).get("w").to_str());
            float h = std::stof(saliente.get("partes").get(i).get("h").to_str());
            float d = std::stof(saliente.get("partes").get(i).get("d").to_str());

            float disX = std::stof(saliente.get("partes").get(i).get("disX").to_str());
            float disY = std::stof(saliente.get("partes").get(i).get("disY").to_str());

            bool lanza {false};

            if (saliente.get("partes").get(i).get("lanzadorrocas").to_str() == "true") {
                lanza = true;
            }

            //std::cout << "Numboxes:" << numboxes << "\n";

            //co.boxes.at(i) = BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, lanza};

            if (numboxes > 0) {
                //std::cout << "i: " << i << "\n";
                co.boxes.insert(co.boxes.begin()+i, BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, lanza});
            }

            //std::cout << "Size:" << co.boxes.size() << "\n";

            i++;
            numboxes--;
        }
    }
 
    co.properties = ColliderComponent_t::P_Saliente;   

    //Agregar al Blackboard
    m_EntMan.getBlackBoard().salientes_bb.emplace_back(&e);

    return e;
}

void GameObjectFactory_t::crearSalientes(const picojson::array &salientes) const {
    for (int i=0; i < salientes.size(); i++) {
        createSaliente(salientes.at(i));
    }   
}

/****************************************************************************************************/
/****************************************NIDOS Y CRIAS***********************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createNido(const picojson::value &nido) const{
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = nido.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = nido.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = nido.get("collider");
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Nido;

    return e;
}

void GameObjectFactory_t::crearNidos(const picojson::array &nidos, const picojson::array &crias) const{
    if (nidos.size() == crias.size()) {
        for (int i=0; i < nidos.size(); i++) {
            auto& n = createNido(nidos.at(i));
            createCria(crias.at(i), n);
        } 
    } else {
        std::cout << "Falta un nido o una cria\n";
    }  
}

ECS::Entity_t& GameObjectFactory_t::createCria(const picojson::value &cria, ECS::Entity_t& follow) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = cria.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = cria.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& fo = m_EntMan.addComponent<FollowComponent_t>(e);
    const picojson::value seguir = cria.get("follow");
    fo.x = std::stoi(seguir.get("x").to_str());
    fo.y = std::stoi(seguir.get("y").to_str());
    fo.z = std::stoi(seguir.get("z").to_str());

    fo.followEntityID = follow.getEntityID();

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = cria.get("collider");
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.properties = ColliderComponent_t::P_Cria;

    return e;
}

/****************************************************************************************************/
/*******************************************ARBUSTOS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createArbusto(const picojson::value &arbusto) const{
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = arbusto.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = arbusto.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = arbusto.get("collider");
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Arbusto;

    //Agregar al Blackboard
    m_EntMan.getBlackBoard().arbustos_bb.emplace_back(&e);

    return e;
}

void GameObjectFactory_t::crearArbustos(const picojson::array &arbustos) const{
    for (int i=0; i < arbustos.size(); i++) {
        createArbusto(arbustos.at(i));
    }       
}

/****************************************************************************************************/
/*******************************************CASCADAS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createCascada(const picojson::value &cascada) const{
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = cascada.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = 90;

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = cascada.get("render");
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo, false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Cascada;

    auto& so = m_EntMan.addComponent<SoundComponent_t>(e);
    so.event_id = "event:/Prueba2";
    so.isEvent3D = true;
    so.marked_for_init = 1;
    so.marked_for_play = 1;

    return e;
}

void GameObjectFactory_t::crearCascadas(const picojson::array &cascadas) const{
    for (int i=0; i < cascadas.size(); i++) {
        createCascada(cascadas.at(i));
    }       
}

/****************************************************************************************************/
/*******************************************SEMILLAS*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createSemilla(const picojson::value &semilla) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = semilla.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& he = m_EntMan.addComponent<HealthComponent_t>(e);

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = semilla.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = semilla.get("collider");
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Semilla;

    return e;
}

void GameObjectFactory_t::crearSemillas(const picojson::array &semillas) const {
    for (int i=0; i < semillas.size(); i++) {
        createSemilla(semillas.at(i));
    }  
}

/****************************************************************************************************/
/******************************************ENGANCHES*************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createEnganche(const picojson::value &enganche) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = enganche.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);

    const picojson::value render = enganche.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = enganche.get("collider");
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}}; 
    co.properties = ColliderComponent_t::P_Control;

    return e;
}

void GameObjectFactory_t::crearEnganches(const picojson::array &enganches) const {
    for (int i=0; i < enganches.size(); i++) {
        createEnganche(enganches.at(i));
    } 
}

/****************************************************************************************************/
/******************************************AGUJEROS**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createAgujero(const picojson::value &agujero) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = agujero.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);

    const picojson::value render = agujero.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = agujero.get("collider");
    co.quesubirbajar = std::stoi(collider.get("quesubirbajar").to_str()); 

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Agujero;
  
    return e;
}

void GameObjectFactory_t::crearAgujeros(const picojson::array &agujeros) const {
    for (int i=0; i < agujeros.size(); i++) {
        createAgujero(agujeros.at(i));
    } 
}

/****************************************************************************************************/
/***************************************TRAMPOLINES**************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createTrampolin(const picojson::value &trampolin) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = trampolin.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = trampolin.get("render");

    re.entityNodes.node.node = motor->createMeshNode(render.get("malla").to_str(), false);

    re.w = std::stof(render.get("w").to_str());
    re.h = std::stof(render.get("h").to_str());
    re.d = std::stof(render.get("d").to_str());

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = trampolin.get("collider");
    co.quesubirbajar = std::stoi(collider.get("quesubirbajar").to_str()); 

    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Trampolin;
  
    return e;
}

void GameObjectFactory_t::crearTrampolines(const picojson::array &trampolines) const {
    for (int i=0; i < trampolines.size(); i++) {
        createTrampolin(trampolines.at(i));
    } 
}

/****************************************************************************************************/
/********************************************MUSGO***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createMusgo(const picojson::value &musgo) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = musgo.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = musgo.get("render");
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Accelerate;

    return e;
}

void GameObjectFactory_t::crearMusgos(const picojson::array &musgos) const {
    for (int i=0; i < musgos.size(); i++) {
        createMusgo(musgos.at(i));
    } 
}

/****************************************************************************************************/
/********************************************HIELO***************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createHielo(const picojson::value &hielo) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = hielo.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = 90;

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = hielo.get("render");
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());
    re.d = std::stoi(render.get("d").to_str());

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.boxes = {{-re.w/2, re.w/2, -re.h/2, re.h/2, -re.d/2, re.d/2}};
    co.properties = ColliderComponent_t::P_Deccelerate;

    return e;
}

void GameObjectFactory_t::crearHielos(const picojson::array &hielos) const {
    for (int i=0; i < hielos.size(); i++) {
        createHielo(hielos.at(i));
    } 
}

/****************************************************************************************************/
/**********************************TUNELES Y FLOTANTES***********************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createPlanosEspeciales(const picojson::value &planoespecial) const{
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = planoespecial.get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = planoespecial.get("render");

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    const picojson::value collider = planoespecial.get("collider");

    if (planoespecial.get("partes").to_str() != "null") {
        int i = 0;

        while (planoespecial.get("partes").get(i).to_str() != "null") {
            float w = std::stof(planoespecial.get("partes").get(i).get("w").to_str());
            float h = std::stof(planoespecial.get("partes").get(i).get("h").to_str());
            float d = std::stof(planoespecial.get("partes").get(i).get("d").to_str());

            float disX = std::stof(planoespecial.get("partes").get(i).get("disX").to_str());
            float disY = std::stof(planoespecial.get("partes").get(i).get("disY").to_str());

            co.boxes.emplace_back(BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, true});

            i++;
        }
    }

    co.properties = ColliderComponent_t::P_PlanoS;
    co.subirbajar = std::stoi(collider.get("subirbajar").to_str());    

    return e;
}

void  GameObjectFactory_t::crearPlanosEspeciales(const picojson::array &planosespeciales) const{
    for (int i=0; i < planosespeciales.size(); i++) {
        createPlanosEspeciales(planosespeciales.at(i));
    } 
}

/****************************************************************************************************/
/********************************************PLANO***************************************************/
/****************************************************************************************************/

void GameObjectFactory_t::crearPlano(const picojson::array &plano) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = plano.at(0).get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = std::stoi(fisica.get("roty").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = plano.at(0).get("render");
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.properties = ColliderComponent_t::P_IsSolid;

    if (plano.at(0).get("partes").to_str() != "null") {
        int i = 0;

        while (plano.at(0).get("partes").get(i).to_str() != "null") {
            float w = std::stof(plano.at(0).get("partes").get(i).get("w").to_str());
            float h = std::stof(plano.at(0).get("partes").get(i).get("h").to_str());
            float d = std::stof(plano.at(0).get("partes").get(i).get("d").to_str());

            float disX = std::stof(plano.at(0).get("partes").get(i).get("disX").to_str());
            float disY = std::stof(plano.at(0).get("partes").get(i).get("disY").to_str());

            co.boxes.emplace_back(BoundingBoxNode_t{-w/2, w/2, -h/2, h/2, -d/2, d/2, false, disX, disY, false});

            i++;
        }
    }
}

/****************************************************************************************************/
/********************************************NAVMESH*************************************************/
/****************************************************************************************************/

void GameObjectFactory_t::crearNavMesh(const picojson::array &plano) const {
    auto& e = m_EntMan.createEntity();

    auto& ph = m_EntMan.addComponent<PhysicsComponent_t>(e);
    const picojson::value fisica = plano.at(0).get("physics");
    ph.x = std::stof(fisica.get("x").to_str());
    ph.y = std::stof(fisica.get("y").to_str());
    ph.z = std::stof(fisica.get("z").to_str());
    ph.roty = std::stoi(fisica.get("roty").to_str());

    auto& re = m_EntMan.addComponent<RenderComponent_t>(e);
    const picojson::value render = plano.at(0).get("render");
    re.w = std::stoi(render.get("w").to_str());
    re.h = std::stoi(render.get("h").to_str());

    std::string modelo = render.get("malla").to_str();
    re.entityNodes.node.node = motor->createMeshNode(modelo,false);

    auto& co = m_EntMan.addComponent<ColliderComponent_t>(e);
    co.properties = ColliderComponent_t::P_IsSolid;

    NavMesh(motor->getNodeVertices(re.entityNodes.node.node), motor->getNodeIndexes(re.entityNodes.node.node));
}

/****************************************************************************************************/
/******************************************PILARES***************************************************/
/****************************************************************************************************/

/****************************************************************************************************/
/********************************************HUD*****************************************************/
/****************************************************************************************************/

ECS::Entity_t& GameObjectFactory_t::createText(std::string padre, std::vector<TextHijo_t> hijos, int32_t xmi, int32_t ymi, int32_t xma, int32_t yma) const {
    auto& e = m_EntMan.createEntity();

    auto& text = m_EntMan.addComponent<TextComponent_t>(e);

    text.texts.texto = padre;
    text.texts.childs = hijos;

    text.xmin = xmi;
    text.ymin = ymi;
    text.xmax = xma;
    text.ymax = yma;

    return e;
}

/****************************************************************************************************/
/****************************************LECTURA DE JSON*********************************************/
/****************************************************************************************************/

void GameObjectFactory_t::loadLevelJSON(std::string_view filename, BehaviourTree_t* tree) const {
    //abrir JSON
    std::ifstream file(filename.data());

    if (!file) { throw std::runtime_error("Imposible abrir JSON file\n"); }

    //leer JSON
    picojson::value json;
    file >> json;

    std::string err { picojson::get_last_error() };

    if (!err.empty()) { throw std::runtime_error(err); }

    const auto& root { json.get<picojson::object>() };

    const auto& player { root.at("player").get<picojson::array>() };
    const auto& enemies { root.at("enemies").get<picojson::array>() };
    const auto& meta { root.at("meta").get<picojson::array>() };

    const auto& salientes { root.at("salientes").get<picojson::array>() };
    const auto& nidos { root.at("nidos").get<picojson::array>() };
    const auto& crias { root.at("crias").get<picojson::array>() };
    const auto& arbustos { root.at("arbustos").get<picojson::array>() };
    const auto& cascadas { root.at("cascadas").get<picojson::array>() };
    const auto& semillas { root.at("semillas").get<picojson::array>() };
    const auto& enganches { root.at("enganches").get<picojson::array>() };
    const auto& agujeros { root.at("agujeros").get<picojson::array>() };
    const auto& trampolines { root.at("trampolines").get<picojson::array>() };

    const auto& plano { root.at("plano").get<picojson::array>() };
    const auto& pilares { root.at("pilares").get<picojson::array>() };

    const auto& musgos { root.at("musgos").get<picojson::array>() };
    const auto& hielos { root.at("hielos").get<picojson::array>() };

    const auto& planosespeciales { root.at("planosespeciales").get<picojson::array>() };

    //const auto& navMesh { root.at("navMesh").get<picojson::array>() };

    auto& pl = createPlayer(player);
    crearEnemigos(tree, enemies);
    createMeta(meta);
    auto& ca = createCamera(0, 30, 640, 360, pl.getEntityID());
    
    crearSalientes(salientes);
    crearNidos(nidos, crias);
    crearArbustos(arbustos);
    crearCascadas(cascadas);
    crearSemillas(semillas);
    crearEnganches(enganches);
    crearAgujeros(agujeros);
    crearTrampolines(trampolines);
    
  //  crearPlano(plano);

   crearMusgos(musgos);
    crearHielos(hielos);

    crearPlanosEspeciales(planosespeciales);
}

//void GameObjectFactory_t::JSONtoBIN(std::string_view jsonfile, std::string_view binfile) const {
//    //abrir JSON
//    std::ifstream filejson(jsonfile.data());
//
//    if (!filejson) { throw std::runtime_error("Imposible abrir JSON file\n"); }
//
//    //abrir BIN
//    std::ofstream filebin(binfile.data(), std::ofstream::binary | std::ofstream::trunc);
//
//    if (!filebin) { throw std::runtime_error("Imposible abrir BIN file for writing\n"); }
//
//    //leer JSON
//    picojson::value json;
//    filejson >> json;
//
//    std::string err { picojson::get_last_error() };
//
//    if (!err.empty()) { throw std::runtime_error(err); }
//
//    const auto& root { json.get<picojson::object>() };
//    const auto& h { static_cast<uint32_t>(root.at("height").get<double>()) };
//    const auto& w { static_cast<uint32_t>(root.at("width").get<double>()) };
//    const auto& map { root.at("map").get<picojson::array>() };
//
//    if (map.size() != w*h) { throw std::runtime_error("Size map error \n"); }
//
//    //escribir en el binario
//    filebin.write(reinterpret_cast<const char*>(&h), sizeof h);
//    filebin.write(reinterpret_cast<const char*>(&w), sizeof w);
//
//    for (auto& elem : map) {
//        const auto& tile { static_cast<uint8_t>(elem.get<double>()) };
//
//        filebin.write(reinterpret_cast<const char*>(&tile), sizeof tile);
//    }
//}

//void GameObjectFactory_t::loadLevelBIN(std::string_view filename) const {
//    //abrir BIN
//    std::ifstream file(filename.data(), std::ifstream::binary);
//
//    if (!file) { throw std::runtime_error("Imposible abrir BIN file for read\n"); }
//
//    //calcular length archivo
//    std::size_t length = [&]() {
//        file.seekg(0, std::ifstream::end);
//        auto len { file.tellg() };
//        file.seekg(0, std::ifstream::beg);
//
//        return len;
//    }();
//
//    //comprobar minimo file size
//    if (length < 8) { throw std::runtime_error("Binary file corrupt. Size too small"); }
//
//    //leer fichero de una sola vez
//    std::vector<char> filemem(length);
//    auto* pfilemem = filemem.data();
//    file.read(pfilemem, length); 
//
//    uint32_t h {}, w {};   
//
//    std::memcpy(&w, pfilemem + 0, sizeof w);
//    std::memcpy(&h, pfilemem + 4, sizeof h);
//
//    if (w*h != (length - 8)) { throw std::runtime_error("Bad size in BIN file level \n"); }
//
//    pfilemem += 8;
//
//    for (uint32_t y = 0; y < h; ++y) {
//        for (uint32_t x = 0; x < w; ++x) {
//            if (*pfilemem) {
//                createPlatform(102*x, 38*y);
//            }
//
//            pfilemem++;
//        }
//    }
//
//    //createLevel1();
//}