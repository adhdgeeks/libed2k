#ifndef __PACKET_STRUCT__
#define __PACKET_STRUCT__

#include <vector>
#include <boost/cstdint.hpp>
#include <boost/optional.hpp>

#include "ctag.hpp"

namespace libed2k
{
    // protocol type
    typedef boost::uint8_t  proto_type;

    //client id or ip type
    typedef boost::uint32_t client_id_type;

    /**
      * print protocol type
     */
    const char* packetToString(proto_type protocol);

    // Client <-> Server
	enum OP_ClientToServerTCP
	{
	    OP_LOGINREQUEST             = 0x01, // <HASH 16><ID 4><PORT 2><1 Tag_set>
		OP_REJECT                   = 0x05, // (null)
		OP_GETSERVERLIST            = 0x14, // (null)client->server
		OP_OFFERFILES               = 0x15, // <count 4>(<HASH 16><ID 4><PORT 2><1 Tag_set>)[count]
		OP_SEARCHREQUEST            = 0x16, // <Query_Tree>
		OP_DISCONNECT               = 0x18, // (not verified)
		OP_GETSOURCES               = 0x19, // <HASH 16>
                                            // v2 <HASH 16><SIZE_4> (17.3) (mandatory on 17.8)
                                            // v2large <HASH 16><FILESIZE 4(0)><FILESIZE 8> (17.9) (large files only)
		OP_SEARCH_USER              = 0x1A, // <Query_Tree>
		OP_CALLBACKREQUEST          = 0x1C, // <ID 4>
		//  OP_QUERY_CHATS          = 0x1D, // (deprecated, not supported by server any longer)
		//  OP_CHAT_MESSAGE         = 0x1E, // (deprecated, not supported by server any longer)
		//  OP_JOIN_ROOM            = 0x1F, // (deprecated, not supported by server any longer)
		OP_QUERY_MORE_RESULT        = 0x21, // ?
		OP_GETSOURCES_OBFU          = 0x23,
		OP_SERVERLIST               = 0x32, // <count 1>(<IP 4><PORT 2>)[count] server->client
		OP_SEARCHRESULT             = 0x33, // <count 4>(<HASH 16><ID 4><PORT 2><1 Tag_set>)[count]
		OP_SERVERSTATUS             = 0x34, // <USER 4><FILES 4>
		OP_CALLBACKREQUESTED        = 0x35, // <IP 4><PORT 2>
		OP_CALLBACK_FAIL            = 0x36, // (null notverified)
		OP_SERVERMESSAGE            = 0x38, // <len 2><Message len>
		//  OP_CHAT_ROOM_REQUEST    = 0x39, // (deprecated, not supported by server any longer)
		//  OP_CHAT_BROADCAST       = 0x3A, // (deprecated, not supported by server any longer)
		//  OP_CHAT_USER_JOIN       = 0x3B, // (deprecated, not supported by server any longer)
		//  OP_CHAT_USER_LEAVE      = 0x3C, // (deprecated, not supported by server any longer)
		//  OP_CHAT_USER            = 0x3D, // (deprecated, not supported by server any longer)
		OP_IDCHANGE                 = 0x40, // <NEW_ID 4>
		OP_SERVERIDENT              = 0x41, // <HASH 16><IP 4><PORT 2>{1 TAG_SET}
		OP_FOUNDSOURCES             = 0x42, // <HASH 16><count 1>(<ID 4><PORT 2>)[count]
		OP_USERS_LIST               = 0x43, // <count 4>(<HASH 16><ID 4><PORT 2><1 Tag_set>)[count]
		OP_FOUNDSOURCES_OBFU = 0x44    // <HASH 16><count 1>(<ID 4><PORT 2><obf settings 1>(UserHash16 if obf&0x08))[count]
	};


	// Client <-> Client
	enum ED2KStandardClientTCP
	{
	    OP_HELLO                    = 0x01, // 0x10<HASH 16><ID 4><PORT 2><1 Tag_set>
	    OP_SENDINGPART              = 0x46, // <HASH 16><von 4><bis 4><Daten len:(von-bis)>
	    OP_REQUESTPARTS             = 0x47, // <HASH 16><von[3] 4*3><bis[3] 4*3>
	    OP_FILEREQANSNOFIL          = 0x48, // <HASH 16>
	    OP_END_OF_DOWNLOAD          = 0x49, // <HASH 16> // Unused for sending
	    OP_ASKSHAREDFILES           = 0x4A, // (null)
	    OP_ASKSHAREDFILESANSWER     = 0x4B, // <count 4>(<HASH 16><ID 4><PORT 2><1 Tag_set>)[count]
	    OP_HELLOANSWER              = 0x4C, // <HASH 16><ID 4><PORT 2><1 Tag_set><SERVER_IP 4><SERVER_PORT 2>
	    OP_CHANGE_CLIENT_ID         = 0x4D, // <ID_old 4><ID_new 4> // Unused for sending
	    OP_MESSAGE                  = 0x4E, // <len 2><Message len>
	    OP_SETREQFILEID             = 0x4F, // <HASH 16>
	    OP_FILESTATUS               = 0x50, // <HASH 16><count 2><status(bit array) len:((count+7)/8)>
	    OP_HASHSETREQUEST           = 0x51, // <HASH 16>
	    OP_HASHSETANSWER            = 0x52, // <count 2><HASH[count] 16*count>
	    OP_STARTUPLOADREQ           = 0x54, // <HASH 16>
	    OP_ACCEPTUPLOADREQ          = 0x55, // (null)
	    OP_CANCELTRANSFER           = 0x56, // (null)
	    OP_OUTOFPARTREQS            = 0x57, // (null)
	    OP_REQUESTFILENAME          = 0x58, // <HASH 16>    (more correctly file_name_request)
	    OP_REQFILENAMEANSWER        = 0x59, // <HASH 16><len 4><NAME len>
	    OP_CHANGE_SLOT              = 0x5B, // <HASH 16> // Not used for sending
	    OP_QUEUERANK                = 0x5C, // <wert  4> (slot index of the request) // Not used for sending
	    OP_ASKSHAREDDIRS            = 0x5D, // (null)
	    OP_ASKSHAREDFILESDIR        = 0x5E, // <len 2><Directory len>
	    OP_ASKSHAREDDIRSANS         = 0x5F, // <count 4>(<len 2><Directory len>)[count]
	    OP_ASKSHAREDFILESDIRANS     = 0x60, // <len 2><Directory len><count 4>(<HASH 16><ID 4><PORT 2><1 T
  	    OP_ASKSHAREDDENIEDANS       = 0x61  // (null)
	};

    // Extended prot client <-> Extended prot client
    enum ED2KExtendedClientTCP {
        OP_EMULEINFO                = 0x01, //
        OP_EMULEINFOANSWER          = 0x02, //
        OP_COMPRESSEDPART           = 0x40, //
        OP_QUEUERANKING             = 0x60, // <RANG 2>
        OP_FILEDESC                 = 0x61, // <len 2><NAME len>
        OP_VERIFYUPSREQ             = 0x71, // (never used)
        OP_VERIFYUPSANSWER          = 0x72, // (never used)
        OP_UDPVERIFYUPREQ           = 0x73, // (never used)
        OP_UDPVERIFYUPA             = 0x74, // (never used)
        OP_REQUESTSOURCES           = 0x81, // <HASH 16>
        OP_ANSWERSOURCES            = 0x82, //
        OP_REQUESTSOURCES2          = 0x83, // <HASH 16>
        OP_ANSWERSOURCES2           = 0x84, //
        OP_PUBLICKEY                = 0x85, // <len 1><pubkey len>
        OP_SIGNATURE                = 0x86, // v1: <len 1><signature len>
        // v2:<len 1><signature len><sigIPused 1>
        OP_SECIDENTSTATE            = 0x87, // <state 1><rndchallenge 4>
        OP_REQUESTPREVIEW           = 0x90, // <HASH 16> // Never used for sending on aMule
        OP_PREVIEWANSWER            = 0x91, // <HASH 16><frames 1>{frames * <len 4><frame len>} // Never used for sending on aMule
        OP_MULTIPACKET              = 0x92,
        OP_MULTIPACKETANSWER        = 0x93,
        // OP_PEERCACHE_QUERY       = 0x94, // Unused on aMule - no PeerCache
        // OP_PEERCACHE_ANSWER      = 0x95, // Unused on aMule - no PeerCache
        // OP_PEERCACHE_ACK         = 0x96, // Unused on aMule - no PeerCache
        OP_PUBLICIP_REQ             = 0x97,
        OP_PUBLICIP_ANSWER          = 0x98,
        OP_CALLBACK                 = 0x99, // <HASH 16><HASH 16><uint 16>
        OP_REASKCALLBACKTCP         = 0x9A,
        OP_AICHREQUEST              = 0x9B, // <HASH 16><uint16><HASH aichhashlen>
        OP_AICHANSWER               = 0x9C, // <HASH 16><uint16><HASH aichhashlen> <data>
        OP_AICHFILEHASHANS          = 0x9D,
        OP_AICHFILEHASHREQ          = 0x9E,
        OP_BUDDYPING                = 0x9F,
        OP_BUDDYPONG                = 0xA0,
        OP_COMPRESSEDPART_I64       = 0xA1, // <HASH 16><von 8><size 4><Data len:size>
        OP_SENDINGPART_I64          = 0xA2, // <HASH 16><start 8><end 8><Data len:(end-start)>
        OP_REQUESTPARTS_I64         = 0xA3, // <HASH 16><start[3] 8*3><end[3] 8*3>
        OP_MULTIPACKET_EXT          = 0xA4,
        OP_CHATCAPTCHAREQ           = 0xA5,
        OP_CHATCAPTCHARES           = 0xA6
    };


	const boost::uint8_t ED2K_SEARCH_OP_EQUAL           = 0;
	const boost::uint8_t ED2K_SEARCH_OP_GREATER         = 1;
	const boost::uint8_t ED2K_SEARCH_OP_LESS            = 2;
	const boost::uint8_t ED2K_SEARCH_OP_GREATER_EQUAL   = 3;
	const boost::uint8_t ED2K_SEARCH_OP_LESS_EQUAL      = 4;
	const boost::uint8_t ED2K_SEARCH_OP_NOTEQUAL        = 5;


	/**
	  * supported protocols
	 */
	const proto_type    OP_EDONKEYHEADER        = '\xE3';
	const proto_type    OP_EDONKEYPROT          = OP_EDONKEYHEADER;
	const proto_type    OP_PACKEDPROT           = '\xD4';
	const proto_type    OP_EMULEPROT            = '\xC5';

    /**
      *  common container holder structure
      *  contains size_type for read it from archives and some container for data
     */
    template<typename size_type, class collection_type>
    struct container_holder
    {
        size_type       m_size;
        collection_type m_collection;
        typedef typename collection_type::iterator Iterator;
        typedef typename collection_type::value_type elem;

        template<typename Archive>
        void save(Archive& ar)
        {
            // save collection size in field with proprly size
            m_size = static_cast<size_type>(m_collection.size());
            ar & m_size;

            for(Iterator i = m_collection.begin(); i != m_collection.end(); ++i)
            {
                ar & *i;
            }

        }

        template<typename Archive>
        void load(Archive& ar)
        {
            ar & m_size;
            m_collection.resize(static_cast<size_t>(m_size));

            for (size_type i = 0; i < m_size; i++)
            {
                ar & m_collection[i];
            }
        }

        /**
          * small helper
         */
        void add(const elem& e)
        {
            m_collection.push_back(e);
        }

        void dump() const
        {
            DBG("container_holder::dump");
            DBG("collection size factor: " << sizeof(size_type));
            DBG("items: " << m_collection.size());
            std::for_each(m_collection.begin(), m_collection.end(), std::mem_fun_ref(&elem::dump));
        }

        LIBED2K_SERIALIZATION_SPLIT_MEMBER()
    };

    /**
      * common libed2k packet header
      *
     */
#pragma pack(push,1)
    struct libed2k_header
    {
        typedef boost::uint32_t size_type;

        proto_type  m_protocol;             //!< protocol identifier
        size_type   m_size;                 //!< packet body size
        proto_type  m_type;                 //!< packet opcode

        /**
          * create empty unknown packet
         */
        libed2k_header() : m_protocol(OP_EDONKEYPROT), m_size(1), m_type(0){}
    };
#pragma pack(pop)

    // common protocol structures

    // file id/port in shared file entry with LowID client
    const boost::uint32_t FILE_COMPLETE_ID      = 0xfbfbfbfbU;
    const boost::uint16_t FILE_COMPLETE_PORT    = 0xfbfbU;
    const boost::uint32_t FILE_INCOMPLETE_ID    = 0xfcfcfcfcU;
    const boost::uint16_t FILE_INCOMPLETE_PORT  = 0xfcfcU;

    struct __file_size
    {

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & nLowPart;

            if (nHighPart > 0)
            {
                ar & nHighPart;
            }
        }

        union
        {
            struct
            {
                boost::uint32_t nLowPart;
                boost::uint32_t nHighPart;
            };

            struct
            {
                boost::uint32_t nLowPart;
                boost::uint32_t nHighPart;
            } u;
            boost::uint64_t     nQuadPart;
        };
    };

    /**
      * common network object identifier in ed2k network
      *
     */
    struct net_identifier
    {
        client_id_type  m_nIP;          //!< client id or ip
        boost::uint16_t m_nPort;        //!< port

        net_identifier();
        net_identifier(boost::uint32_t nIP, boost::uint16_t nPort);

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_nIP;
            ar & m_nPort;
        }

        void dump() const;
    };

    /**
      * shared file item structure in offer list
     */
    struct shared_file_entry
    {
        md4_hash                    m_hFile;            //!< md4 file hash
        net_identifier              m_network_point;    //!< network identification
        tag_list<boost::uint32_t>   m_list;             //!< file information list


        shared_file_entry();
        shared_file_entry(const md4_hash& hFile, boost::uint32_t nFileId, boost::uint16_t nPort);

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_network_point;
            ar & m_list;
        }

        void dump() const;
    };

    //!< client <-> server messages

    /**
      * login request structure - contain some info and 4 tag items
     */
    struct cs_login_request
    {
        md4_hash                    m_hClient;
        net_identifier              m_sNetIdentifier;
        tag_list<boost::uint32_t>   m_list;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hClient;
            ar & m_sNetIdentifier;
            ar & m_list;
        }
    };

    /**
      * server text message
     */
    struct server_message
    {
        boost::uint16_t m_nLength;
        std::string     m_strMessage;
        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_nLength;
            // allocate buffer if it needs
            if (m_strMessage.size() != m_nLength)
            {
                m_strMessage.resize(m_nLength);
            }

            ar & m_strMessage;
        }
    };

    /**
      * empty structure for get servers list from server
     */
    typedef container_holder<boost::uint8_t, std::vector<net_identifier> > server_list;
    typedef container_holder<boost::uint32_t, std::vector<shared_file_entry> > offer_files_list;

    /**
      * structure contain server IP/port, hash and some information tags
     */
    struct server_info_entry
    {
        md4_hash                    m_hServer;
        net_identifier              m_address;
        tag_list<boost::uint32_t>   m_list;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hServer;
            ar & m_address;
            ar & m_list;
        }
    };

    struct id_change
    {
        client_id_type  m_nClientId;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_nClientId;
        }
    };

    /**
      * callback request from server to client
     */
    struct callback_request_in
    {
        net_identifier  m_network_point;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_network_point;
        }
    };

    /**
      * callback request failed
     */
    struct callback_req_fail
    {
        boost::uint32_t m_nClientId;
    };

    /**
      * callback request from client to server
     */
    struct callback_request_out
    {
        client_id_type      m_nClientId;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_nClientId;
        }
    };

    /**
      * server status structure
     */
    struct server_status
    {
        boost::uint32_t m_nUserCount;
        boost::uint32_t m_nFilesCount;

        template<typename Archive>
        void serialize(Archive & ar)
        {
            ar & m_nUserCount;
            ar & m_nFilesCount;
        }
    };

    /**
      * common search request structure
     */
    class search_request_entry
    {
    public:
        enum SRE_Operation
        {
            SRE_AND     = 0,
            SRE_OR      = 1,
            SRE_NOT     = 2
        };
        search_request_entry(SRE_Operation soper);
        search_request_entry(const std::string& strValue);
        search_request_entry(tg_type nMetaTagId, const std::string& strValue);
        search_request_entry(const std::string strMetaTagName, const std::string& strValue);
        search_request_entry(tg_type nMetaTagId, boost::uint8_t nOperator, boost::uint64_t nValue);
        search_request_entry(const std::string& strMetaTagName, boost::uint8_t nOperator, boost::uint64_t nValue);

        void load(archive::ed2k_iarchive& ar)
        {
            // do nothing - we never load this structure
        }

        void save(archive::ed2k_oarchive& ar);

        LIBED2K_SERIALIZATION_SPLIT_MEMBER()
    private:
        tg_type         m_type;
        boost::uint8_t  m_operator;     //!< operator
        std::string     m_strValue;     //!< string value

        union
        {
            boost::uint64_t m_nValue64;       //!< numeric value
            boost::uint32_t m_nValue32;
        };

        boost::optional<tg_type>         m_meta_type;    //!< meta type
        boost::optional<std::string>     m_strMetaName;  //!< meta name
    };

    /**
      * request more search result from server  - it is empty structure
     */
    struct search_more_result
    {
        template<typename Archive>
        void serialize(Archive& ar)
        {
            // do nothing
        }
    };


    /**
      * structure contains one entry in search result list - it is server answer
     */
    struct search_file_entry
    {
    	md4_hash					m_hFile;		    //!< file hash
    	net_identifier              m_network_point;    //!< client network identification
    	tag_list<boost::uint32_t>	m_list;			    //!< tag list with additional data - file name,size,sources ...

    	template<typename Archive>
    	void serialize(Archive& ar)
    	{
    	    ar & m_hFile;
    	    ar & m_network_point;
    	    ar & m_list;
    	}

    	void dump() const;
    };

    typedef container_holder<boost::uint32_t, std::vector<search_file_entry> > search_file_list;

    /**
      * this structure holds search requests to eDonkey server
      *
     */
    struct search_request
    {
        void add_entry(const search_request_entry& entry);

        template<typename Archive>
        void serialize(Archive& ar)
        {
            for (size_t n = 0; n < m_entries.size(); n++)
            {
                ar & m_entries[n];
            }
        }
    private:
        std::vector<search_request_entry> m_entries;
    };

    /**
      * request sources for file
     */
    struct get_file_sources
    {
        md4_hash        m_hFile;        //!< file hash
        __file_size     m_file_size;    //!< file size

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;

            // ugly eDonkey protocol need empty 32-bit part before 64-bit file size record
            if (m_file_size.nHighPart > 0)
            {
                boost::uint32_t nZeroSize = 0;
                ar & nZeroSize;
            }

            ar & m_file_size;

        }
    };

    /**
      * file sources found structure
     */
    struct found_file_sources
    {
        md4_hash    m_hFile;
        container_holder<boost::uint8_t, std::vector<net_identifier> > m_sources;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_sources;
        }

        void dump() const;
    };


    /**
      * structure for get packet opcode from structure type
     */
    template<typename T> struct packet_type;

    //OP_REJECT                   = 0x05
    //OP_GETSERVERLIST            = 0x14
    //OP_DISCONNECT               = 0x18, // (not verified)
    //OP_SEARCH_USER              = 0x1A, // <Query_Tree>
    //OP_FOUNDSOURCES_OBFU = 0x44    // <HASH 16><count 1>(<ID 4><PORT 2><obf settings 1>(UserHash16 if obf&0x08))[count]
    //OP_USERS_LIST               = 0x43, // <count 4>(<HASH 16><ID 4><PORT 2><1 Tag_set>)[count]

    template<> struct packet_type<cs_login_request>         { static const proto_type value = OP_LOGINREQUEST;  };      //!< on login to server
    template<> struct packet_type<offer_files_list>         { static const proto_type value = OP_OFFERFILES;    };      //!< offer files to server

    template<> struct packet_type<search_request>           { static const proto_type value = OP_SEARCHREQUEST; };      //!< search request to server
    template<> struct packet_type<search_file_list>         { static const proto_type value = OP_SEARCHRESULT;  };      //!< search result from server
    template<> struct packet_type<search_more_result>       { static const proto_type value = OP_QUERY_MORE_RESULT;  }; //!< search result from server

    template<> struct packet_type<get_file_sources>         { static const proto_type value = OP_GETSOURCES;    };      //!< file sources request to server
    template<> struct packet_type<found_file_sources>       { static const proto_type value = OP_FOUNDSOURCES;  };      //!< file sources answer

    template<> struct packet_type<callback_request_out>     { static const proto_type value = OP_CALLBACKREQUEST;};     //!< callback request to server - do not use
    template<> struct packet_type<callback_request_in>      { static const proto_type value = OP_CALLBACKREQUESTED; };  //!< callback request from server - we reject it
    template<> struct packet_type<callback_req_fail>        { static const proto_type value = OP_CALLBACK_FAIL; };      //!< callback request answer from server

    template<> struct packet_type<server_list>              { static const proto_type value = OP_SERVERLIST;    };      //!< server list from server
    template<> struct packet_type<server_status>            { static const proto_type value = OP_SERVERSTATUS;  };      //!< server status
    template<> struct packet_type<id_change>                { static const proto_type value = OP_IDCHANGE;      };      //!< new our id from server
    template<> struct packet_type<server_message>           { static const proto_type value = OP_SERVERMESSAGE; };      //!< some server message
    template<> struct packet_type<server_info_entry>        { static const proto_type value = OP_SERVERIDENT;   };      //!< server info


    // Client to Client structures
    struct client_hello
    {
        boost::uint8_t              m_nHashLength;          //!< clients hash length
        md4_hash                    m_hClient;              //!< hash
        net_identifier              m_sNetIdentifier;       //!< client network identification
        tag_list<boost::uint32_t>   m_tlist;                //!< tag list for additional information

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hClient;
            ar & m_sNetIdentifier;
            ar & m_tlist;
        }
    };

    struct client_hello_answer
    {
        md4_hash                    m_hClient;
        net_identifier              m_sNetIdentifier;
        tag_list<boost::uint32_t>   m_tlist;
        net_identifier              m_sServerIdentifier;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hClient;
            ar & m_sNetIdentifier;
            ar & m_tlist;
            ar & m_sServerIdentifier;
        }
    };

    struct client_file_request
    {
        md4_hash m_hFile;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
        }
    };

    struct client_no_file
    {
        md4_hash m_hFile;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
        }
    };

    struct client_file_status
    {
        md4_hash m_hFile;
        container_holder<boost::uint16_t, std::vector<unsigned char> > m_vcStatus;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_vcStatus;
        }
    };

    struct client_hashset_request
    {
        md4_hash m_hFile;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
        }
    };

    struct client_hashset_answer
    {
        md4_hash m_hFile;
        container_holder<boost::uint16_t, std::vector<md4_hash> > m_vhParts;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_vhParts;
        }
    };

    struct client_start_upload
    {
        md4_hash m_hFile;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
        }
    };

    struct client_queue_ranking
    {
        boost::uint16_t m_nRank;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_nRank;
        }
    };

    struct client_accept_upload
    {
        template<typename Archive>
        void serialize(Archive& ar)
        {
        }
    };

    struct client_cancel_transfer
    {
        template<typename Archive>
        void serialize(Archive& ar)
        {
        }
    };

    template <typename size_type>
    struct client_request_parts
    {
        md4_hash  m_hFile;
        size_type m_begin_offset_1;
        size_type m_begin_offset_2;
        size_type m_begin_offset_3;
        size_type m_end_offset_1;
        size_type m_end_offset_2;
        size_type m_end_offset_3;

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_begin_offset_1;
            ar & m_begin_offset_2;
            ar & m_begin_offset_3;
            ar & m_end_offset_1;
            ar & m_end_offset_2;
            ar & m_end_offset_3;
        }
    };

    typedef client_request_parts<boost::uint32_t> client_request_parts_32;
    typedef client_request_parts<boost::uint64_t> client_request_parts_64;

    template <typename size_type>
    struct client_sending_part
    {
        md4_hash m_hFile;
        size_type m_begin_offset;
        size_type m_end_offset;
        // user_data[end-begin]

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_begin_offset;
            ar & m_end_offset;
            // user_data[end-begin]
        }

    };

    typedef client_sending_part<boost::uint32_t> client_sending_part_32;
    typedef client_sending_part<boost::uint64_t> client_sending_part_64;

    template <typename size_type>
    struct client_compressed_part
    {
        md4_hash m_hFile;
        size_type m_begin_offset;
        boost::uint32_t m_compressed_size;
        // user_data[compressed_size]

        template<typename Archive>
        void serialize(Archive& ar)
        {
            ar & m_hFile;
            ar & m_begin_offset;
            ar & m_compressed_size;
            // compressed_user_data[compressed_size]
        }
    };

    typedef client_compressed_part<boost::uint32_t> client_compressed_part_32;
    typedef client_compressed_part<boost::uint64_t> client_compressed_part_64;

    template<> struct packet_type<client_hello> {
        static const proto_type value = OP_HELLO;
    };
    template<> struct packet_type<client_hello_answer> {
        static const proto_type value = OP_HELLOANSWER;
    };
    template<> struct packet_type<client_file_request> {
        static const proto_type value = OP_SETREQFILEID;
    };
    template<> struct packet_type<client_no_file> {
        static const proto_type value = OP_FILEREQANSNOFIL;
    };
    template<> struct packet_type<client_file_status> {
        static const proto_type value = OP_FILESTATUS;
    };
    template<> struct packet_type<client_hashset_request> {
        static const proto_type value = OP_HASHSETREQUEST;
    };
    template<> struct packet_type<client_hashset_answer> {
        static const proto_type value = OP_HASHSETANSWER;
    };
    template<> struct packet_type<client_start_upload> {
        static const proto_type value = OP_STARTUPLOADREQ;
    };
    template<> struct packet_type<client_queue_ranking> {
        static const proto_type value = OP_QUEUERANKING;
    };
    template<> struct packet_type<client_accept_upload> {
        static const proto_type value = OP_ACCEPTUPLOADREQ;
    };
    template<> struct packet_type<client_cancel_transfer> {
        static const proto_type value = OP_CANCELTRANSFER;
    };
    template<> struct packet_type<client_request_parts_32> {
        static const proto_type value = OP_REQUESTPARTS;
    };
    template<> struct packet_type<client_request_parts_64> {
        static const proto_type value = OP_REQUESTPARTS_I64;
    };
    template<> struct packet_type<client_sending_part_32> {
        static const proto_type value = OP_SENDINGPART;
    };
    template<> struct packet_type<client_sending_part_64> {
        static const proto_type value = OP_SENDINGPART_I64;
    };
    template<> struct packet_type<client_compressed_part_32> {
        static const proto_type value = OP_COMPRESSEDPART;
    };
    template<> struct packet_type<client_compressed_part_64> {
        static const proto_type value = OP_COMPRESSEDPART_I64;
    };
}


#endif //__PACKET_STRUCT__
