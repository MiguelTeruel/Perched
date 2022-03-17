#pragma once
#include <iostream>
#include <vector>
#include <initializer_list>
#include "node.hpp"


struct BTNodeSequence_t : BTNode_t{

    using value_type        = BTNode_t*;
    using container_type    = std::vector<value_type>;
    using init_list         = std::initializer_list<value_type>;
    using iterator          = std::vector<value_type>::iterator;

    BTNodeSequence_t (init_list l) : nodes(l){}

    void resetSequence(){ currentNodeIt = nodes.begin();}

    BTNodeStatus_t run(EntityContext_t &ectx) noexcept final{
        if (!ectx.ia->running_node.empty()){
            if(ectx.ia->running_node.contains(this)){
                currentNodeIt = ectx.ia->running_node[this];
            }
        }
        if (currentNodeIt == nodes.end()){
            resetSequence();
        }
        auto status = (*currentNodeIt)->run(ectx);
        switch(status){
            case BTNodeStatus_t::fail:      { 
                if(ectx.ia->running_node.contains(this)){
                    ectx.ia->running_node.erase(this);
                }
            
                resetSequence();
                return BTNodeStatus_t::fail;
            }
            case BTNodeStatus_t::running:   { 
                ectx.ia->running_node.try_emplace(this, currentNodeIt);
                resetSequence(); 
                return BTNodeStatus_t::running;
            }
            case BTNodeStatus_t::success: {
                ++currentNodeIt;
                if (currentNodeIt == nodes.end()){
                    if(ectx.ia->running_node.contains(this)){
                        ectx.ia->running_node.erase(this);
                    }
                    resetSequence();
                    return BTNodeStatus_t::success;
                }
            }

        }
        if (ectx.ia->running_node.contains(this)){
            ectx.ia->running_node[this] = currentNodeIt;
        }else{
            ectx.ia->running_node.try_emplace(this, currentNodeIt);
        }
        
        resetSequence();
        return BTNodeStatus_t::running;
    }

    private:
        container_type  nodes{};
        iterator        currentNodeIt  {nodes.begin()};

};