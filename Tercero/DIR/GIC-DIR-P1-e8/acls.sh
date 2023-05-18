# Acl del router de la oficina

enable

conf t



no ip access-list extended vlan400-in
ip access-list extended vlan400-in
permit udp any 10.3.12.0 0.0.1.255 eq domain
permit tcp any 10.3.0.0 0.0.1.255 eq www
permit tcp any 10.3.6.0 0.0.1.255 eq www
end
write

exit

interface FastEthernet0/0.400
ip access-group vlan400-in in
exit

no ip access-list extended vlanDNS-in
ip access-list extended vlanDNS-in
permit udp 10.3.12.0 0.0.1.255 eq domain 10.0.48.0 0.0.15.255
permit tcp any 10.3.0.0 0.0.1.255 eq www
permit tcp any 10.3.6.0 0.0.1.255 eq www
end
write