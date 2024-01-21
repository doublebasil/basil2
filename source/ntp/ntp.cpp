#include "ntp.hpp"

#include "settings.hpp"
#include "oled.hpp"

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "lwip/dns.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"

#include "hardware/rtc.h"

typedef struct {
    ip_addr_t ntpServerAddress;
    bool dnsRequestSent;
    struct udp_pcb *ntpPcb; // User Datagram Protocol, Network Time Protocol, Protocol Control Block
    absolute_time_t ntpTestTime;
    t_globalData* globalDataPtr; // So that the callback has access to global data
    int tcpipLinkState;
    bool ntpServerFound;
} t_ntp;
#define NTP_SERVER "pool.ntp.org"
#define NTP_MSG_LEN 48
#define NTP_PORT 123
#define NTP_DELTA 2208988800 // seconds between 1 Jan 1900 and 1 Jan 1970

static t_ntp m_ntpState;
bool rtcSet = false;

static void m_ntpRecievedCallback(void *arg, struct udp_pcb *pcb, struct pbuf *p, 
    const ip_addr_t *addr, u16_t port);
static void m_printDnsCodeToTerminal( int dnsReturnCode );
static void m_ntpSendRequest( void );
static void m_dnsCallback( const char *name, const ip_addr_t *ipaddress, void *arg );

int ntp_doTheNtpStuff( void )
{
    m_ntpState.ntpPcb = udp_new_ip_type( IPADDR_TYPE_ANY );
    m_ntpState.ntpServerFound = false;
    m_ntpState.tcpipLinkState = CYW43_LINK_DOWN;
    udp_recv( m_ntpState.ntpPcb, m_ntpRecievedCallback, &m_ntpState );

    absolute_time_t lastAttemptTimestamp = nil_time;
    uint8_t connectionAttempts = 0U;

    while( ( rtcSet == false ) && ( connectionAttempts < NTP_MAX_ATTEMPTS ) )
    {
        if( is_nil_time( lastAttemptTimestamp ) 
            || ( absolute_time_diff_us( lastAttemptTimestamp, get_absolute_time() ) > NTP_RESEND_DELAY_US ) )
        {
            lastAttemptTimestamp = get_absolute_time();
            oled_terminalWrite( "------------------" );
            m_ntpSendRequest();
            ++connectionAttempts;
        }
        if( rtcSet == true )
            break;

        sleep_ms( 50 );
    }
    if( rtcSet == false )
    {
        return 1;
    }

    return 0;
}

static void m_ntpRecievedCallback(void *arg, struct udp_pcb *pcb, struct pbuf *p, 
    const ip_addr_t *addr, u16_t port)
{
    oled_terminalWrite( "NTP received ");

    t_ntp* ntpStatePtr = (t_ntp*) arg;
    uint8_t mode = pbuf_get_at(p, 0) & 0x7;
    uint8_t stratum = pbuf_get_at(p, 1);

    // Check the result
    if( ( ip_addr_cmp( addr, &(ntpStatePtr->ntpServerAddress) ) )
        && ( port == NTP_PORT ) 
        && ( p->tot_len == NTP_MSG_LEN )
        && ( mode == 0x4 )
        && ( stratum != 0 ) )
    {
        uint8_t secondsBuf[4] = {0};
        pbuf_copy_partial(p, secondsBuf, sizeof(secondsBuf), 40);
        uint32_t secondsSince1900 = secondsBuf[0] << 24 | secondsBuf[1] << 16 | secondsBuf[2] << 8 | secondsBuf[3];
        uint32_t secondsSince1970 = secondsSince1900 - NTP_DELTA;
        time_t epoch = secondsSince1970 + ( 0LL * 60LL * 60LL ); // Change 0 to 8 for UTC+8;

        struct tm *utc = gmtime( &epoch );

        datetime_t rtcTime;
        rtcTime.year = utc->tm_year + 1900;
        rtcTime.month= utc->tm_mon + 1;
        rtcTime.day = utc->tm_mday;
        rtcTime.hour = utc->tm_hour;
        rtcTime.min = utc->tm_min;
        rtcTime.sec = utc->tm_sec;
        rtcTime.dotw = utc->tm_wday;

        // Now set the pico's RTC
        if( !rtc_set_datetime( &rtcTime ) )
            oled_terminalWrite( "Error setting RTC" );  
        else
        {
            oled_terminalWrite( "RTC set" );
            char textBuffer[30];
            snprintf( textBuffer, sizeof( textBuffer ), "%d/%d/%d", utc->tm_mday, utc->tm_mon + 1, utc->tm_year + 1900 );
            oled_terminalWrite( textBuffer );
            snprintf( textBuffer, sizeof( textBuffer ), "%02d:%02d:%02d", utc->tm_hour, utc->tm_min, utc->tm_sec );
            oled_terminalWrite( textBuffer );
            rtcSet = true;
        }
    }
    else
    {
        oled_terminalWrite( "Invalid NTP reply" );
    }
    pbuf_free(p);
}

static void m_printDnsCodeToTerminal( int dnsReturnCode )
{
    if( dnsReturnCode == ERR_OK )
        oled_terminalWrite( "DNS OK" );

    else if( dnsReturnCode == ERR_MEM )
        oled_terminalWrite( "DNS ERR_MEM" );

    else if( dnsReturnCode == ERR_BUF )
        oled_terminalWrite( "DNS ERR_BUF" );

    else if( dnsReturnCode == ERR_TIMEOUT )
        oled_terminalWrite( "DNS ERR_TIMEOUT" );

    else if( dnsReturnCode == ERR_RTE )
        oled_terminalWrite( "DNS ERR_RTE" );

    else if( dnsReturnCode == ERR_INPROGRESS )
        oled_terminalWrite( "DNS ERR_INPROGRESS" );

    else if( dnsReturnCode == ERR_VAL )
        oled_terminalWrite( "DNS ERR_VAL" );

    else if( dnsReturnCode == ERR_WOULDBLOCK )
        oled_terminalWrite( "DNS ERR_WOULDBLOCK" );

    else if( dnsReturnCode == ERR_USE )
        oled_terminalWrite( "DNS ERR_USE" );

    else if( dnsReturnCode == ERR_ALREADY )
        oled_terminalWrite( "DNS ERR_ALREADY" );

    else if( dnsReturnCode == ERR_ISCONN )
        oled_terminalWrite( "DNS ERR_ISCONN" );

    else if( dnsReturnCode == ERR_CONN )
        oled_terminalWrite( "DNS ERR_CONN" );

    else if( dnsReturnCode == ERR_IF )
        oled_terminalWrite( "DNS ERR_IF" );

    else if( dnsReturnCode == ERR_ABRT )
        oled_terminalWrite( "DNS ERR_ABRT" );

    else if( dnsReturnCode == ERR_RST )
        oled_terminalWrite( "DNS ERR_RST" );

    else if( dnsReturnCode == ERR_CLSD )
        oled_terminalWrite( "DNS ERR_CLSD" );

    else if( dnsReturnCode == ERR_ARG )
        oled_terminalWrite( "DNS ERR_ARG" );

    else
        oled_terminalWrite( "DNS ERR UNKNOWN" );
}

static void m_ntpSendRequest( void )
{
    oled_terminalWrite( "Getting DNS" );
    int dnsReturnCode;
    uint8_t attempts = 0U;
    while( attempts < DNS_MAX_RETRIES )
    {
        cyw43_arch_lwip_begin();
        dnsReturnCode = dns_gethostbyname( NTP_SERVER, &m_ntpState.ntpServerAddress, m_dnsCallback, &m_ntpState );
        cyw43_arch_lwip_end();

        m_printDnsCodeToTerminal( dnsReturnCode );

        if( dnsReturnCode == ERR_OK )
            break;

        ++attempts;
    }
    if( dnsReturnCode != ERR_OK )
        return; // Failed

    oled_terminalWrite( "Got NTP IP:" );
    char textBuffer[30];
    snprintf( textBuffer, sizeof( textBuffer ), "%s", ipaddr_ntoa( &m_ntpState.ntpServerAddress ) );
    oled_terminalWrite( textBuffer );
    sleep_ms( MESSAGE_READ_DELAY_MS );

    oled_terminalWrite( "" );
    oled_terminalWrite( "Sending request..." );

    cyw43_arch_lwip_begin();
    struct pbuf *pb = pbuf_alloc( PBUF_TRANSPORT, NTP_MSG_LEN, PBUF_RAM );
    uint8_t *req = (uint8_t*) pb->payload;
    memset( req, 0, NTP_MSG_LEN );
    req[0] = 0x1b;   // 0x00 011 011 (LI:00, VN:3(version), MODE:3 (client))
    udp_sendto( m_ntpState.ntpPcb, pb, &m_ntpState.ntpServerAddress, NTP_PORT );
    pbuf_free( pb );
    cyw43_arch_lwip_end();
}

static void m_dnsCallback( const char *name, const ip_addr_t *ipaddress, void *arg )
{
    t_ntp* ntpDataPtr = (t_ntp*) arg;
    ntpDataPtr->ntpServerAddress = *ipaddress;
    ntpDataPtr->ntpServerFound = true;
}
