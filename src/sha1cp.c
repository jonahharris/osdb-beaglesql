static const char  rcsfile []= "$Header: /home/magrasjc/test/src/RCS/sha1cp.c,v 0.87.2.1 2000/02/05 06:13:43 magrasjc Exp $";
void __declspec(naked) __cdecl SHA1Transform(unsigned long* H, unsigned long* x)
{
  __asm{
	push ebp
	push esi
	push edi
	push ebx
	mov edx, [esp+24]
	sub esp, 320

	mov edi, [edx]
	mov ebp, [edx+4]
	bswap edi
	bswap ebp
	mov [esp], edi
	mov [esp+4], ebp
	mov edi, [edx+8]
	mov ebp, [edx+12]
	bswap edi
	bswap ebp
	mov [esp+8], edi
	mov [esp+12], ebp
	mov edi, [edx+16]
	mov ebp, [edx+20]
	bswap edi
	bswap ebp
	mov [esp+16], edi
	mov [esp+20], ebp
	mov edi, [edx+24]
	mov ebp, [edx+28]
	bswap edi
	bswap ebp
	mov [esp+24], edi
	mov [esp+28], ebp
	mov edi, [edx+32]
	mov ebp, [edx+36]
	bswap edi
	bswap ebp
	mov [esp+32], edi
	mov [esp+36], ebp
	mov edi, [edx+40]
	mov ebp, [edx+44]
	bswap edi
	bswap ebp
	mov [esp+40], edi
	mov [esp+44], ebp
	mov edi, [edx+48]
	mov ebp, [edx+52]
	bswap edi
	bswap ebp
	mov [esp+48], edi
	mov [esp+52], ebp
	mov edi, [edx+56]
	mov ebp, [edx+60]
	bswap edi
	bswap ebp
	mov [esp+56], edi
	mov [esp+60], ebp
	mov edi, [esp+32]
	mov ebp, [esp+36]
	mov ecx, [esp+52]
	mov ebx, [esp+56]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+8]
	mov ebp, [esp+12]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp]
	mov ebp, [esp+4]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+40]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+44]
	mov [esp+64], ecx
	mov [esp+68], ebx
	mov ecx, [esp+60]
	mov ebx, [esp+64]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+16]
	mov ebp, [esp+20]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+8]
	mov ebp, [esp+12]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+48]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+52]
	mov [esp+72], ecx
	mov [esp+76], ebx
	mov ecx, [esp+68]
	mov ebx, [esp+72]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+24]
	mov ebp, [esp+28]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+16]
	mov ebp, [esp+20]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+56]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+60]
	mov [esp+80], ecx
	mov [esp+84], ebx
	mov ecx, [esp+76]
	mov ebx, [esp+80]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+32]
	mov ebp, [esp+36]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+24]
	mov ebp, [esp+28]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+64]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+68]
	mov [esp+88], ecx
	mov [esp+92], ebx
	mov ecx, [esp+84]
	mov ebx, [esp+88]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+40]
	mov ebp, [esp+44]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+32]
	mov ebp, [esp+36]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+72]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+76]
	mov [esp+96], ecx
	mov [esp+100], ebx
	mov ecx, [esp+92]
	mov ebx, [esp+96]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+48]
	mov ebp, [esp+52]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+40]
	mov ebp, [esp+44]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+80]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+84]
	mov [esp+104], ecx
	mov [esp+108], ebx
	mov ecx, [esp+100]
	mov ebx, [esp+104]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+56]
	mov ebp, [esp+60]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+48]
	mov ebp, [esp+52]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+88]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+92]
	mov [esp+112], ecx
	mov [esp+116], ebx
	mov ecx, [esp+108]
	mov ebx, [esp+112]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+64]
	mov ebp, [esp+68]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+56]
	mov ebp, [esp+60]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+96]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+100]
	mov [esp+120], ecx
	mov [esp+124], ebx
	mov ecx, [esp+116]
	mov ebx, [esp+120]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+72]
	mov ebp, [esp+76]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+64]
	mov ebp, [esp+68]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+104]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+108]
	mov [esp+128], ecx
	mov [esp+132], ebx
	mov ecx, [esp+124]
	mov ebx, [esp+128]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+80]
	mov ebp, [esp+84]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+72]
	mov ebp, [esp+76]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+112]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+116]
	mov [esp+136], ecx
	mov [esp+140], ebx
	mov ecx, [esp+132]
	mov ebx, [esp+136]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+88]
	mov ebp, [esp+92]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+80]
	mov ebp, [esp+84]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+120]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+124]
	mov [esp+144], ecx
	mov [esp+148], ebx
	mov ecx, [esp+140]
	mov ebx, [esp+144]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+96]
	mov ebp, [esp+100]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+88]
	mov ebp, [esp+92]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+128]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+132]
	mov [esp+152], ecx
	mov [esp+156], ebx
	mov ecx, [esp+148]
	mov ebx, [esp+152]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+104]
	mov ebp, [esp+108]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+96]
	mov ebp, [esp+100]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+136]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+140]
	mov [esp+160], ecx
	mov [esp+164], ebx
	mov ecx, [esp+156]
	mov ebx, [esp+160]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+112]
	mov ebp, [esp+116]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+104]
	mov ebp, [esp+108]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+144]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+148]
	mov [esp+168], ecx
	mov [esp+172], ebx
	mov ecx, [esp+164]
	mov ebx, [esp+168]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+120]
	mov ebp, [esp+124]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+112]
	mov ebp, [esp+116]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+152]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+156]
	mov [esp+176], ecx
	mov [esp+180], ebx
	mov ecx, [esp+172]
	mov ebx, [esp+176]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+128]
	mov ebp, [esp+132]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+120]
	mov ebp, [esp+124]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+160]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+164]
	mov [esp+184], ecx
	mov [esp+188], ebx
	mov ecx, [esp+180]
	mov ebx, [esp+184]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+136]
	mov ebp, [esp+140]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+128]
	mov ebp, [esp+132]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+168]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+172]
	mov [esp+192], ecx
	mov [esp+196], ebx
	mov ecx, [esp+188]
	mov ebx, [esp+192]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+144]
	mov ebp, [esp+148]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+136]
	mov ebp, [esp+140]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+176]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+180]
	mov [esp+200], ecx
	mov [esp+204], ebx
	mov ecx, [esp+196]
	mov ebx, [esp+200]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+152]
	mov ebp, [esp+156]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+144]
	mov ebp, [esp+148]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+184]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+188]
	mov [esp+208], ecx
	mov [esp+212], ebx
	mov ecx, [esp+204]
	mov ebx, [esp+208]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+160]
	mov ebp, [esp+164]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+152]
	mov ebp, [esp+156]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+192]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+196]
	mov [esp+216], ecx
	mov [esp+220], ebx
	mov ecx, [esp+212]
	mov ebx, [esp+216]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+168]
	mov ebp, [esp+172]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+160]
	mov ebp, [esp+164]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+200]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+204]
	mov [esp+224], ecx
	mov [esp+228], ebx
	mov ecx, [esp+220]
	mov ebx, [esp+224]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+176]
	mov ebp, [esp+180]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+168]
	mov ebp, [esp+172]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+208]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+212]
	mov [esp+232], ecx
	mov [esp+236], ebx
	mov ecx, [esp+228]
	mov ebx, [esp+232]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+184]
	mov ebp, [esp+188]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+176]
	mov ebp, [esp+180]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+216]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+220]
	mov [esp+240], ecx
	mov [esp+244], ebx
	mov ecx, [esp+236]
	mov ebx, [esp+240]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+192]
	mov ebp, [esp+196]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+184]
	mov ebp, [esp+188]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+224]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+228]
	mov [esp+248], ecx
	mov [esp+252], ebx
	mov ecx, [esp+244]
	mov ebx, [esp+248]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+200]
	mov ebp, [esp+204]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+192]
	mov ebp, [esp+196]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+232]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+236]
	mov [esp+256], ecx
	mov [esp+260], ebx
	mov ecx, [esp+252]
	mov ebx, [esp+256]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+208]
	mov ebp, [esp+212]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+200]
	mov ebp, [esp+204]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+240]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+244]
	mov [esp+264], ecx
	mov [esp+268], ebx
	mov ecx, [esp+260]
	mov ebx, [esp+264]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+216]
	mov ebp, [esp+220]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+208]
	mov ebp, [esp+212]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+248]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+252]
	mov [esp+272], ecx
	mov [esp+276], ebx
	mov ecx, [esp+268]
	mov ebx, [esp+272]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+224]
	mov ebp, [esp+228]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+216]
	mov ebp, [esp+220]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+256]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+260]
	mov [esp+280], ecx
	mov [esp+284], ebx
	mov ecx, [esp+276]
	mov ebx, [esp+280]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+232]
	mov ebp, [esp+236]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+224]
	mov ebp, [esp+228]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+264]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+268]
	mov [esp+288], ecx
	mov [esp+292], ebx
	mov ecx, [esp+284]
	mov ebx, [esp+288]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+240]
	mov ebp, [esp+244]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+232]
	mov ebp, [esp+236]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+272]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+276]
	mov [esp+296], ecx
	mov [esp+300], ebx
	mov ecx, [esp+292]
	mov ebx, [esp+296]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+248]
	mov ebp, [esp+252]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+240]
	mov ebp, [esp+244]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	mov edi, [esp+280]
	_emit 0xd1
	_emit 0xc3
	mov ebp, [esp+284]
	mov [esp+304], ecx
	mov [esp+308], ebx
	mov ecx, [esp+300]
	mov ebx, [esp+304]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+256]
	mov ebp, [esp+260]
	xor ecx, edi
	xor ebx, ebp
	mov edi, [esp+248]
	mov ebp, [esp+252]
	xor ecx, edi
	xor ebx, ebp
	_emit 0xd1
	_emit 0xc1
	_emit 0xd1
	_emit 0xc3
	mov [esp+312], ecx
	mov [esp+316], ebx
	mov eax, [esp+340]
	mov ebx, [eax+4]
	mov ecx, [eax+8]
	mov edx, [eax+12]
	mov edi, [eax+16]
	mov eax, [eax]
	mov ebp, ecx
/* Subround 0 */
	xor ebp, edx
	and ebp, ebx
	mov esi, eax
	rol esi, 5
	add edi, esi
	mov esi, [esp]
	_emit 0xd1
	_emit 203
	xor ebp, edx
	_emit 0xd1
	_emit 203
	lea edi, [edi+esi+1518500249]
	add edi, ebp
/* Subround 1 */
	mov esi, ebx
	xor esi, ecx
	mov ebp, edi
	rol ebp, 5
	and esi, eax
	add edx, ebp
	_emit 0xd1
	_emit 200
	mov ebp, [esp+4]
	_emit 0xd1
	_emit 200
	xor esi, ecx
	lea edx, [edx+ebp+1518500249]
	mov ebp, eax
	add edx, esi
/* Subround 2 */
	xor ebp, ebx
	and ebp, edi
	mov esi, edx
	rol esi, 5
	add ecx, esi
	mov esi, [esp+8]
	_emit 0xd1
	_emit 207
	xor ebp, ebx
	_emit 0xd1
	_emit 207
	lea ecx, [ecx+esi+1518500249]
	add ecx, ebp
/* Subround 3 */
	mov esi, edi
	xor esi, eax
	mov ebp, ecx
	rol ebp, 5
	and esi, edx
	add ebx, ebp
	_emit 0xd1
	_emit 202
	mov ebp, [esp+12]
	_emit 0xd1
	_emit 202
	xor esi, eax
	lea ebx, [ebx+ebp+1518500249]
	mov ebp, edx
	add ebx, esi
/* Subround 4 */
	xor ebp, edi
	and ebp, ecx
	mov esi, ebx
	rol esi, 5
	add eax, esi
	mov esi, [esp+16]
	_emit 0xd1
	_emit 201
	xor ebp, edi
	_emit 0xd1
	_emit 201
	lea eax, [eax+esi+1518500249]
	add eax, ebp
/* Subround 5 */
	mov esi, ecx
	xor esi, edx
	mov ebp, eax
	rol ebp, 5
	and esi, ebx
	add edi, ebp
	_emit 0xd1
	_emit 203
	mov ebp, [esp+20]
	_emit 0xd1
	_emit 203
	xor esi, edx
	lea edi, [edi+ebp+1518500249]
	mov ebp, ebx
	add edi, esi
/* Subround 6 */
	xor ebp, ecx
	and ebp, eax
	mov esi, edi
	rol esi, 5
	add edx, esi
	mov esi, [esp+24]
	_emit 0xd1
	_emit 200
	xor ebp, ecx
	_emit 0xd1
	_emit 200
	lea edx, [edx+esi+1518500249]
	add edx, ebp
/* Subround 7 */
	mov esi, eax
	xor esi, ebx
	mov ebp, edx
	rol ebp, 5
	and esi, edi
	add ecx, ebp
	_emit 0xd1
	_emit 207
	mov ebp, [esp+28]
	_emit 0xd1
	_emit 207
	xor esi, ebx
	lea ecx, [ecx+ebp+1518500249]
	mov ebp, edi
	add ecx, esi
/* Subround 8 */
	xor ebp, eax
	and ebp, edx
	mov esi, ecx
	rol esi, 5
	add ebx, esi
	mov esi, [esp+32]
	_emit 0xd1
	_emit 202
	xor ebp, eax
	_emit 0xd1
	_emit 202
	lea ebx, [ebx+esi+1518500249]
	add ebx, ebp
/* Subround 9 */
	mov esi, edx
	xor esi, edi
	mov ebp, ebx
	rol ebp, 5
	and esi, ecx
	add eax, ebp
	_emit 0xd1
	_emit 201
	mov ebp, [esp+36]
	_emit 0xd1
	_emit 201
	xor esi, edi
	lea eax, [eax+ebp+1518500249]
	mov ebp, ecx
	add eax, esi
/* Subround 10 */
	xor ebp, edx
	and ebp, ebx
	mov esi, eax
	rol esi, 5
	add edi, esi
	mov esi, [esp+40]
	_emit 0xd1
	_emit 203
	xor ebp, edx
	_emit 0xd1
	_emit 203
	lea edi, [edi+esi+1518500249]
	add edi, ebp
/* Subround 11 */
	mov esi, ebx
	xor esi, ecx
	mov ebp, edi
	rol ebp, 5
	and esi, eax
	add edx, ebp
	_emit 0xd1
	_emit 200
	mov ebp, [esp+44]
	_emit 0xd1
	_emit 200
	xor esi, ecx
	lea edx, [edx+ebp+1518500249]
	mov ebp, eax
	add edx, esi
/* Subround 12 */
	xor ebp, ebx
	and ebp, edi
	mov esi, edx
	rol esi, 5
	add ecx, esi
	mov esi, [esp+48]
	_emit 0xd1
	_emit 207
	xor ebp, ebx
	_emit 0xd1
	_emit 207
	lea ecx, [ecx+esi+1518500249]
	add ecx, ebp
/* Subround 13 */
	mov esi, edi
	xor esi, eax
	mov ebp, ecx
	rol ebp, 5
	and esi, edx
	add ebx, ebp
	_emit 0xd1
	_emit 202
	mov ebp, [esp+52]
	_emit 0xd1
	_emit 202
	xor esi, eax
	lea ebx, [ebx+ebp+1518500249]
	mov ebp, edx
	add ebx, esi
/* Subround 14 */
	xor ebp, edi
	and ebp, ecx
	mov esi, ebx
	rol esi, 5
	add eax, esi
	mov esi, [esp+56]
	_emit 0xd1
	_emit 201
	xor ebp, edi
	_emit 0xd1
	_emit 201
	lea eax, [eax+esi+1518500249]
	add eax, ebp
/* Subround 15 */
	mov esi, ecx
	xor esi, edx
	mov ebp, eax
	rol ebp, 5
	and esi, ebx
	add edi, ebp
	_emit 0xd1
	_emit 203
	mov ebp, [esp+60]
	_emit 0xd1
	_emit 203
	xor esi, edx
	lea edi, [edi+ebp+1518500249]
	mov ebp, ebx
	add edi, esi
/* Subround 16 */
	xor ebp, ecx
	and ebp, eax
	mov esi, edi
	rol esi, 5
	add edx, esi
	mov esi, [esp+64]
	_emit 0xd1
	_emit 200
	xor ebp, ecx
	_emit 0xd1
	_emit 200
	lea edx, [edx+esi+1518500249]
	add edx, ebp
/* Subround 17 */
	mov esi, eax
	xor esi, ebx
	mov ebp, edx
	rol ebp, 5
	and esi, edi
	add ecx, ebp
	_emit 0xd1
	_emit 207
	mov ebp, [esp+68]
	_emit 0xd1
	_emit 207
	xor esi, ebx
	lea ecx, [ecx+ebp+1518500249]
	mov ebp, edi
	add ecx, esi
/* Subround 18 */
	xor ebp, eax
	and ebp, edx
	mov esi, ecx
	rol esi, 5
	add ebx, esi
	mov esi, [esp+72]
	_emit 0xd1
	_emit 202
	xor ebp, eax
	_emit 0xd1
	_emit 202
	lea ebx, [ebx+esi+1518500249]
	add ebx, ebp
/* Subround 19 */
	mov esi, edx
	xor esi, edi
	mov ebp, ebx
	rol ebp, 5
	and esi, ecx
	add eax, ebp
	_emit 0xd1
	_emit 201
	mov ebp, [esp+76]
	_emit 0xd1
	_emit 201
	xor esi, edi
	lea eax, [eax+ebp+1518500249]
	mov ebp, ecx
	add eax, esi
/* Subround 20 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+80]
	lea edi, [edi+ebp+1859775393]
	mov ebp, ebx
	add edi, esi
/* Subround 21 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+84]
	lea edx, [edx+ebp+1859775393]
	mov ebp, eax
	add edx, esi
/* Subround 22 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+88]
	lea ecx, [ecx+ebp+1859775393]
	mov ebp, edi
	add ecx, esi
/* Subround 23 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+92]
	lea ebx, [ebx+ebp+1859775393]
	mov ebp, edx
	add ebx, esi
/* Subround 24 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+96]
	lea eax, [eax+ebp+1859775393]
	mov ebp, ecx
	add eax, esi
/* Subround 25 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+100]
	lea edi, [edi+ebp+1859775393]
	mov ebp, ebx
	add edi, esi
/* Subround 26 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+104]
	lea edx, [edx+ebp+1859775393]
	mov ebp, eax
	add edx, esi
/* Subround 27 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+108]
	lea ecx, [ecx+ebp+1859775393]
	mov ebp, edi
	add ecx, esi
/* Subround 28 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+112]
	lea ebx, [ebx+ebp+1859775393]
	mov ebp, edx
	add ebx, esi
/* Subround 29 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+116]
	lea eax, [eax+ebp+1859775393]
	mov ebp, ecx
	add eax, esi
/* Subround 30 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+120]
	lea edi, [edi+ebp+1859775393]
	mov ebp, ebx
	add edi, esi
/* Subround 31 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+124]
	lea edx, [edx+ebp+1859775393]
	mov ebp, eax
	add edx, esi
/* Subround 32 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+128]
	lea ecx, [ecx+ebp+1859775393]
	mov ebp, edi
	add ecx, esi
/* Subround 33 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+132]
	lea ebx, [ebx+ebp+1859775393]
	mov ebp, edx
	add ebx, esi
/* Subround 34 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+136]
	lea eax, [eax+ebp+1859775393]
	mov ebp, ecx
	add eax, esi
/* Subround 35 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+140]
	lea edi, [edi+ebp+1859775393]
	mov ebp, ebx
	add edi, esi
/* Subround 36 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+144]
	lea edx, [edx+ebp+1859775393]
	mov ebp, eax
	add edx, esi
/* Subround 37 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+148]
	lea ecx, [ecx+ebp+1859775393]
	mov ebp, edi
	add ecx, esi
/* Subround 38 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+152]
	lea ebx, [ebx+ebp+1859775393]
	mov ebp, edx
	add ebx, esi
/* Subround 39 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+156]
	lea eax, [eax+ebp+1859775393]
	mov ebp, ecx
	add eax, esi
/* Subround 40 */
	mov ebp, ebx
	mov esi, eax
	rol esi, 5
	or ebp, ecx
	add edi, esi
	and ebp, edx
	mov esi, [esp+160]
	add edi, esi
	mov esi, ebx
	and esi, ecx
	add edi, -1894007588
	_emit 0xd1
	_emit 203
	or esi, ebp
	_emit 0xd1
	_emit 203
	add edi, esi
/* Subround 41 */
	mov ebp, eax
	mov esi, edi
	rol esi, 5
	or ebp, ebx
	add edx, esi
	and ebp, ecx
	mov esi, [esp+164]
	add edx, esi
	mov esi, eax
	and esi, ebx
	add edx, -1894007588
	_emit 0xd1
	_emit 200
	or esi, ebp
	_emit 0xd1
	_emit 200
	add edx, esi
/* Subround 42 */
	mov ebp, edi
	mov esi, edx
	rol esi, 5
	or ebp, eax
	add ecx, esi
	and ebp, ebx
	mov esi, [esp+168]
	add ecx, esi
	mov esi, edi
	and esi, eax
	add ecx, -1894007588
	_emit 0xd1
	_emit 207
	or esi, ebp
	_emit 0xd1
	_emit 207
	add ecx, esi
/* Subround 43 */
	mov ebp, edx
	mov esi, ecx
	rol esi, 5
	or ebp, edi
	add ebx, esi
	and ebp, eax
	mov esi, [esp+172]
	add ebx, esi
	mov esi, edx
	and esi, edi
	add ebx, -1894007588
	_emit 0xd1
	_emit 202
	or esi, ebp
	_emit 0xd1
	_emit 202
	add ebx, esi
/* Subround 44 */
	mov ebp, ecx
	mov esi, ebx
	rol esi, 5
	or ebp, edx
	add eax, esi
	and ebp, edi
	mov esi, [esp+176]
	add eax, esi
	mov esi, ecx
	and esi, edx
	add eax, -1894007588
	_emit 0xd1
	_emit 201
	or esi, ebp
	_emit 0xd1
	_emit 201
	add eax, esi
/* Subround 45 */
	mov ebp, ebx
	mov esi, eax
	rol esi, 5
	or ebp, ecx
	add edi, esi
	and ebp, edx
	mov esi, [esp+180]
	add edi, esi
	mov esi, ebx
	and esi, ecx
	add edi, -1894007588
	_emit 0xd1
	_emit 203
	or esi, ebp
	_emit 0xd1
	_emit 203
	add edi, esi
/* Subround 46 */
	mov ebp, eax
	mov esi, edi
	rol esi, 5
	or ebp, ebx
	add edx, esi
	and ebp, ecx
	mov esi, [esp+184]
	add edx, esi
	mov esi, eax
	and esi, ebx
	add edx, -1894007588
	_emit 0xd1
	_emit 200
	or esi, ebp
	_emit 0xd1
	_emit 200
	add edx, esi
/* Subround 47 */
	mov ebp, edi
	mov esi, edx
	rol esi, 5
	or ebp, eax
	add ecx, esi
	and ebp, ebx
	mov esi, [esp+188]
	add ecx, esi
	mov esi, edi
	and esi, eax
	add ecx, -1894007588
	_emit 0xd1
	_emit 207
	or esi, ebp
	_emit 0xd1
	_emit 207
	add ecx, esi
/* Subround 48 */
	mov ebp, edx
	mov esi, ecx
	rol esi, 5
	or ebp, edi
	add ebx, esi
	and ebp, eax
	mov esi, [esp+192]
	add ebx, esi
	mov esi, edx
	and esi, edi
	add ebx, -1894007588
	_emit 0xd1
	_emit 202
	or esi, ebp
	_emit 0xd1
	_emit 202
	add ebx, esi
/* Subround 49 */
	mov ebp, ecx
	mov esi, ebx
	rol esi, 5
	or ebp, edx
	add eax, esi
	and ebp, edi
	mov esi, [esp+196]
	add eax, esi
	mov esi, ecx
	and esi, edx
	add eax, -1894007588
	_emit 0xd1
	_emit 201
	or esi, ebp
	_emit 0xd1
	_emit 201
	add eax, esi
/* Subround 50 */
	mov ebp, ebx
	mov esi, eax
	rol esi, 5
	or ebp, ecx
	add edi, esi
	and ebp, edx
	mov esi, [esp+200]
	add edi, esi
	mov esi, ebx
	and esi, ecx
	add edi, -1894007588
	_emit 0xd1
	_emit 203
	or esi, ebp
	_emit 0xd1
	_emit 203
	add edi, esi
/* Subround 51 */
	mov ebp, eax
	mov esi, edi
	rol esi, 5
	or ebp, ebx
	add edx, esi
	and ebp, ecx
	mov esi, [esp+204]
	add edx, esi
	mov esi, eax
	and esi, ebx
	add edx, -1894007588
	_emit 0xd1
	_emit 200
	or esi, ebp
	_emit 0xd1
	_emit 200
	add edx, esi
/* Subround 52 */
	mov ebp, edi
	mov esi, edx
	rol esi, 5
	or ebp, eax
	add ecx, esi
	and ebp, ebx
	mov esi, [esp+208]
	add ecx, esi
	mov esi, edi
	and esi, eax
	add ecx, -1894007588
	_emit 0xd1
	_emit 207
	or esi, ebp
	_emit 0xd1
	_emit 207
	add ecx, esi
/* Subround 53 */
	mov ebp, edx
	mov esi, ecx
	rol esi, 5
	or ebp, edi
	add ebx, esi
	and ebp, eax
	mov esi, [esp+212]
	add ebx, esi
	mov esi, edx
	and esi, edi
	add ebx, -1894007588
	_emit 0xd1
	_emit 202
	or esi, ebp
	_emit 0xd1
	_emit 202
	add ebx, esi
/* Subround 54 */
	mov ebp, ecx
	mov esi, ebx
	rol esi, 5
	or ebp, edx
	add eax, esi
	and ebp, edi
	mov esi, [esp+216]
	add eax, esi
	mov esi, ecx
	and esi, edx
	add eax, -1894007588
	_emit 0xd1
	_emit 201
	or esi, ebp
	_emit 0xd1
	_emit 201
	add eax, esi
/* Subround 55 */
	mov ebp, ebx
	mov esi, eax
	rol esi, 5
	or ebp, ecx
	add edi, esi
	and ebp, edx
	mov esi, [esp+220]
	add edi, esi
	mov esi, ebx
	and esi, ecx
	add edi, -1894007588
	_emit 0xd1
	_emit 203
	or esi, ebp
	_emit 0xd1
	_emit 203
	add edi, esi
/* Subround 56 */
	mov ebp, eax
	mov esi, edi
	rol esi, 5
	or ebp, ebx
	add edx, esi
	and ebp, ecx
	mov esi, [esp+224]
	add edx, esi
	mov esi, eax
	and esi, ebx
	add edx, -1894007588
	_emit 0xd1
	_emit 200
	or esi, ebp
	_emit 0xd1
	_emit 200
	add edx, esi
/* Subround 57 */
	mov ebp, edi
	mov esi, edx
	rol esi, 5
	or ebp, eax
	add ecx, esi
	and ebp, ebx
	mov esi, [esp+228]
	add ecx, esi
	mov esi, edi
	and esi, eax
	add ecx, -1894007588
	_emit 0xd1
	_emit 207
	or esi, ebp
	_emit 0xd1
	_emit 207
	add ecx, esi
/* Subround 58 */
	mov ebp, edx
	mov esi, ecx
	rol esi, 5
	or ebp, edi
	add ebx, esi
	and ebp, eax
	mov esi, [esp+232]
	add ebx, esi
	mov esi, edx
	and esi, edi
	add ebx, -1894007588
	_emit 0xd1
	_emit 202
	or esi, ebp
	_emit 0xd1
	_emit 202
	add ebx, esi
/* Subround 59 */
	mov ebp, ecx
	mov esi, ebx
	rol esi, 5
	or ebp, edx
	add eax, esi
	and ebp, edi
	mov esi, [esp+236]
	add eax, esi
	mov esi, ecx
	and esi, edx
	add eax, -1894007588
	_emit 0xd1
	_emit 201
	or esi, ebp
	_emit 0xd1
	_emit 201
	add eax, esi
	mov ebp, ecx
/* Subround 60 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+240]
	lea edi, [edi+ebp+-899497514]
	mov ebp, ebx
	add edi, esi
/* Subround 61 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+244]
	lea edx, [edx+ebp+-899497514]
	mov ebp, eax
	add edx, esi
/* Subround 62 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+248]
	lea ecx, [ecx+ebp+-899497514]
	mov ebp, edi
	add ecx, esi
/* Subround 63 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+252]
	lea ebx, [ebx+ebp+-899497514]
	mov ebp, edx
	add ebx, esi
/* Subround 64 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+256]
	lea eax, [eax+ebp+-899497514]
	mov ebp, ecx
	add eax, esi
/* Subround 65 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+260]
	lea edi, [edi+ebp+-899497514]
	mov ebp, ebx
	add edi, esi
/* Subround 66 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+264]
	lea edx, [edx+ebp+-899497514]
	mov ebp, eax
	add edx, esi
/* Subround 67 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+268]
	lea ecx, [ecx+ebp+-899497514]
	mov ebp, edi
	add ecx, esi
/* Subround 68 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+272]
	lea ebx, [ebx+ebp+-899497514]
	mov ebp, edx
	add ebx, esi
/* Subround 69 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+276]
	lea eax, [eax+ebp+-899497514]
	mov ebp, ecx
	add eax, esi
/* Subround 70 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+280]
	lea edi, [edi+ebp+-899497514]
	mov ebp, ebx
	add edi, esi
/* Subround 71 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+284]
	lea edx, [edx+ebp+-899497514]
	mov ebp, eax
	add edx, esi
/* Subround 72 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+288]
	lea ecx, [ecx+ebp+-899497514]
	mov ebp, edi
	add ecx, esi
/* Subround 73 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+292]
	lea ebx, [ebx+ebp+-899497514]
	mov ebp, edx
	add ebx, esi
/* Subround 74 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+296]
	lea eax, [eax+ebp+-899497514]
	mov ebp, ecx
	add eax, esi
/* Subround 75 */
	xor ebp, ebx
	xor ebp, edx
	mov esi, eax
	rol esi, 5
	_emit 0xd1
	_emit 203
	add edi, esi
	_emit 0xd1
	_emit 203
	mov esi, [esp+300]
	lea edi, [edi+ebp+-899497514]
	mov ebp, ebx
	add edi, esi
/* Subround 76 */
	xor ebp, eax
	xor ebp, ecx
	mov esi, edi
	rol esi, 5
	_emit 0xd1
	_emit 200
	add edx, esi
	_emit 0xd1
	_emit 200
	mov esi, [esp+304]
	lea edx, [edx+ebp+-899497514]
	mov ebp, eax
	add edx, esi
/* Subround 77 */
	xor ebp, edi
	xor ebp, ebx
	mov esi, edx
	rol esi, 5
	_emit 0xd1
	_emit 207
	add ecx, esi
	_emit 0xd1
	_emit 207
	mov esi, [esp+308]
	lea ecx, [ecx+ebp+-899497514]
	mov ebp, edi
	add ecx, esi
/* Subround 78 */
	xor ebp, edx
	xor ebp, eax
	mov esi, ecx
	rol esi, 5
	_emit 0xd1
	_emit 202
	add ebx, esi
	_emit 0xd1
	_emit 202
	mov esi, [esp+312]
	lea ebx, [ebx+ebp+-899497514]
	mov ebp, edx
	add ebx, esi
/* Subround 79 */
	xor ebp, ecx
	xor ebp, edi
	mov esi, ebx
	rol esi, 5
	_emit 0xd1
	_emit 201
	add eax, esi
	_emit 0xd1
	_emit 201
	mov esi, [esp+316]
	lea eax, [eax+ebp+-899497514]
	mov ebp, ecx
	add eax, esi
	mov esi, [esp+340]
	add esp, 320
	mov ebp, [esi+16]
	add edi, ebp
	mov [esi+16], edi
	mov ebp, [esi]
	mov edi, [esi+4]
	add eax, ebp
	add ebx, edi
	mov [esi], eax
	mov [esi+4], ebx
	mov ebp, [esi+8]
	mov edi, [esi+12]
	add ecx, ebp
	add edx, edi
	mov [esi+8], ecx
	mov [esi+12], edx

	pop ebx
	pop edi
	pop esi
	pop ebp

	ret
  }
}
