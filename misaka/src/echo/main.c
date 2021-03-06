#include "misaka.h"
#include "link.h"
#include "task.h"

//register link and event here
int core_register()
{

    struct peer *peer;
    echo_register();   

    SET_DEBUG(DEBUG_DEBUG);
    misaka_config.role = ROLE_SERVER;
#if 0
    //register udp 
    peer  =  udp_init("192.168.97.98", 8000, 11112);
    if(!peer){
        fprintf(stderr, "init peer fail\n");
	    return -1;
    }

    peer->pack =    echo_pack;
    peer->unpack =  echo_unpack;
    peer->role = ROLE_SERVER;
    peer->drole = ROLE_UDP;
    peer_register(peer);
    misaka_start(peer);

#endif

#if 1
    peer = tcp_listen_init(TCP_DSTPORT);
    peer->listens = 3;
    peer->pack = echo_pack;
    peer->unpack = echo_unpack;
    peer->role = ROLE_SERVER;
    peer->drole = ROLE_TCP;
    peer_register(peer);
    misaka_start(peer);

#endif

#if 0
    peer = tcp_connect_init("127.0.0.1", TCP_DSTPORT, 11000);
    peer->role = ROLE_TCP;
    peer->drole = ROLE_SERVER;
    peer_register(peer);
    misaka_start(peer);
#endif

    return 0;
}

int main(int argc, char **argv)
{
	int background =0;
	int  opt,i;
	while ((opt = getopt(argc, argv, "dhf:l:S:B:C:N:")) != -1) {
               switch (opt) {
			case 'd':
				background = 1;
				break;
			default:
				return 1;
		}
	}

	if (background)
	    daemon(0, 1);
        
        core_init();

        core_register();

        core_run();
        
        return 0;
}

