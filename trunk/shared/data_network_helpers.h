//
//  data_network_helpers.h
//  server
//
//  Created by Ryan Sheffer on 2013-03-29.
//  Copyright (c) 2013 Ryan Sheffer. All rights reserved.
//

#ifndef DATA_NETWORK_HELPERS
#define DATA_NETWORK_HELPERS

namespace DataPacking
{
    /**
     * The max name length of a network entity
     */
    const unsigned int MAX_NETWORK_NAME_LEN        = 64;
    
    /** Network flag sent with each entity datamap */
    enum net_ent_flags
    {
        /** Specifies an empty entity slot, will also destory any
         entity currently in the client slot. */
        NET_FLAG_DEAD       =   0x01,
        
        /** Specifies that the entity is new. */
        NET_FLAG_CREATE     =   0x02,
        
        /** Specifies that this data is an update for an old entity. */
        NET_FLAG_UPDATE     =   0x04
    };
    
    /** The heading structure before an entities data map */
    struct networked_entity_header_t
    {
        /** Number of Saved Objects. */
        short       num_objs;
        
        /**
         * The network name of the entity, the name which is common between the
         * source of this entity and the destination.
         */
        //char        networkName[MAX_NETWORK_NAME_LEN];
    };
}

#endif // DATA_NETWORK_HELPERS
