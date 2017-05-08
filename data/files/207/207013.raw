# Julia wrapper for header: /Users/dls/jl/openssl-1.0.1e/include/openssl/ocsp.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0

@c Ptr{OCSP_RESPID} OCSP_RESPID_new () libopenssl
@c None OCSP_RESPID_free (Ptr{OCSP_RESPID},) libopenssl
@c Ptr{OCSP_RESPID} d2i_OCSP_RESPID (Ptr{Ptr{OCSP_RESPID}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_RESPID (Ptr{OCSP_RESPID}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_CERTID} OCSP_CERTID_dup (Ptr{OCSP_CERTID},) libopenssl
@c Ptr{OCSP_RESPONSE} OCSP_sendreq_bio (Ptr{BIO}, Ptr{Uint8}, Ptr{OCSP_REQUEST}) libopenssl
@c Ptr{OCSP_REQ_CTX} OCSP_sendreq_new (Ptr{BIO}, Ptr{Uint8}, Ptr{OCSP_REQUEST}, Int32) libopenssl
@c Int32 OCSP_sendreq_nbio (Ptr{Ptr{OCSP_RESPONSE}}, Ptr{OCSP_REQ_CTX}) libopenssl
@c None OCSP_REQ_CTX_free (Ptr{OCSP_REQ_CTX},) libopenssl
@c Int32 OCSP_REQ_CTX_set1_req (Ptr{OCSP_REQ_CTX}, Ptr{OCSP_REQUEST}) libopenssl
@c Int32 OCSP_REQ_CTX_add1_header (Ptr{OCSP_REQ_CTX}, Ptr{Uint8}, Ptr{Uint8}) libopenssl
@c Ptr{OCSP_CERTID} OCSP_cert_to_id (Ptr{EVP_MD}, Ptr{X509}, Ptr{X509}) libopenssl
@c Ptr{OCSP_CERTID} OCSP_cert_id_new (Ptr{EVP_MD}, Ptr{X509_NAME}, Ptr{ASN1_BIT_STRING}, Ptr{ASN1_INTEGER}) libopenssl
@c Ptr{OCSP_ONEREQ} OCSP_request_add0_id (Ptr{OCSP_REQUEST}, Ptr{OCSP_CERTID}) libopenssl
@c Int32 OCSP_request_add1_nonce (Ptr{OCSP_REQUEST}, Ptr{Uint8}, Int32) libopenssl
@c Int32 OCSP_basic_add1_nonce (Ptr{OCSP_BASICRESP}, Ptr{Uint8}, Int32) libopenssl
@c Int32 OCSP_check_nonce (Ptr{OCSP_REQUEST}, Ptr{OCSP_BASICRESP}) libopenssl
@c Int32 OCSP_copy_nonce (Ptr{OCSP_BASICRESP}, Ptr{OCSP_REQUEST}) libopenssl
@c Int32 OCSP_request_set1_name (Ptr{OCSP_REQUEST}, Ptr{X509_NAME}) libopenssl
@c Int32 OCSP_request_add1_cert (Ptr{OCSP_REQUEST}, Ptr{X509}) libopenssl
@c Int32 OCSP_request_sign (Ptr{OCSP_REQUEST}, Ptr{X509}, Ptr{EVP_PKEY}, Ptr{EVP_MD}, Ptr{STACK}, Uint64) libopenssl
@c Int32 OCSP_response_status (Ptr{OCSP_RESPONSE},) libopenssl
@c Ptr{OCSP_BASICRESP} OCSP_response_get1_basic (Ptr{OCSP_RESPONSE},) libopenssl
@c Int32 OCSP_resp_count (Ptr{OCSP_BASICRESP},) libopenssl
@c Ptr{OCSP_SINGLERESP} OCSP_resp_get0 (Ptr{OCSP_BASICRESP}, Int32) libopenssl
@c Int32 OCSP_resp_find (Ptr{OCSP_BASICRESP}, Ptr{OCSP_CERTID}, Int32) libopenssl
@c Int32 OCSP_single_get0_status (Ptr{OCSP_SINGLERESP}, Ptr{Int32}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}) libopenssl
@c Int32 OCSP_resp_find_status (Ptr{OCSP_BASICRESP}, Ptr{OCSP_CERTID}, Ptr{Int32}, Ptr{Int32}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}) libopenssl
@c Int32 OCSP_check_validity (Ptr{ASN1_GENERALIZEDTIME}, Ptr{ASN1_GENERALIZEDTIME}, Int64, Int64) libopenssl
@c Int32 OCSP_request_verify (Ptr{OCSP_REQUEST}, Ptr{STACK}, Ptr{X509_STORE}, Uint64) libopenssl
@c Int32 OCSP_parse_url (Ptr{Uint8}, Ptr{Ptr{Uint8}}, Ptr{Ptr{Uint8}}, Ptr{Ptr{Uint8}}, Ptr{Int32}) libopenssl
@c Int32 OCSP_id_issuer_cmp (Ptr{OCSP_CERTID}, Ptr{OCSP_CERTID}) libopenssl
@c Int32 OCSP_id_cmp (Ptr{OCSP_CERTID}, Ptr{OCSP_CERTID}) libopenssl
@c Int32 OCSP_request_onereq_count (Ptr{OCSP_REQUEST},) libopenssl
@c Ptr{OCSP_ONEREQ} OCSP_request_onereq_get0 (Ptr{OCSP_REQUEST}, Int32) libopenssl
@c Ptr{OCSP_CERTID} OCSP_onereq_get0_id (Ptr{OCSP_ONEREQ},) libopenssl
@c Int32 OCSP_id_get0_info (Ptr{Ptr{ASN1_OCTET_STRING}}, Ptr{Ptr{ASN1_OBJECT}}, Ptr{Ptr{ASN1_OCTET_STRING}}, Ptr{Ptr{ASN1_INTEGER}}, Ptr{OCSP_CERTID}) libopenssl
@c Int32 OCSP_request_is_signed (Ptr{OCSP_REQUEST},) libopenssl
@c Ptr{OCSP_RESPONSE} OCSP_response_create (Int32, Ptr{OCSP_BASICRESP}) libopenssl
@c Ptr{OCSP_SINGLERESP} OCSP_basic_add1_status (Ptr{OCSP_BASICRESP}, Ptr{OCSP_CERTID}, Int32, Int32, Ptr{ASN1_TIME}, Ptr{ASN1_TIME}, Ptr{ASN1_TIME}) libopenssl
@c Int32 OCSP_basic_add1_cert (Ptr{OCSP_BASICRESP}, Ptr{X509}) libopenssl
@c Int32 OCSP_basic_sign (Ptr{OCSP_BASICRESP}, Ptr{X509}, Ptr{EVP_PKEY}, Ptr{EVP_MD}, Ptr{STACK}, Uint64) libopenssl
@c Ptr{X509_EXTENSION} OCSP_crlID_new (Ptr{Uint8}, Ptr{Int64}, Ptr{Uint8}) libopenssl
@c Ptr{X509_EXTENSION} OCSP_accept_responses_new (Ptr{Ptr{Uint8}},) libopenssl
@c Ptr{X509_EXTENSION} OCSP_archive_cutoff_new (Ptr{Uint8},) libopenssl
@c Ptr{X509_EXTENSION} OCSP_url_svcloc_new (Ptr{X509_NAME}, Ptr{Ptr{Uint8}}) libopenssl
@c Int32 OCSP_REQUEST_get_ext_count (Ptr{OCSP_REQUEST},) libopenssl
@c Int32 OCSP_REQUEST_get_ext_by_NID (Ptr{OCSP_REQUEST}, Int32, Int32) libopenssl
@c Int32 OCSP_REQUEST_get_ext_by_OBJ (Ptr{OCSP_REQUEST}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Int32 OCSP_REQUEST_get_ext_by_critical (Ptr{OCSP_REQUEST}, Int32, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_REQUEST_get_ext (Ptr{OCSP_REQUEST}, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_REQUEST_delete_ext (Ptr{OCSP_REQUEST}, Int32) libopenssl
@c Ptr{None} OCSP_REQUEST_get1_ext_d2i (Ptr{OCSP_REQUEST}, Int32, Ptr{Int32}, Ptr{Int32}) libopenssl
@c Int32 OCSP_REQUEST_add1_ext_i2d (Ptr{OCSP_REQUEST}, Int32, Ptr{None}, Int32, Uint64) libopenssl
@c Int32 OCSP_REQUEST_add_ext (Ptr{OCSP_REQUEST}, Ptr{X509_EXTENSION}, Int32) libopenssl
@c Int32 OCSP_ONEREQ_get_ext_count (Ptr{OCSP_ONEREQ},) libopenssl
@c Int32 OCSP_ONEREQ_get_ext_by_NID (Ptr{OCSP_ONEREQ}, Int32, Int32) libopenssl
@c Int32 OCSP_ONEREQ_get_ext_by_OBJ (Ptr{OCSP_ONEREQ}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Int32 OCSP_ONEREQ_get_ext_by_critical (Ptr{OCSP_ONEREQ}, Int32, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_ONEREQ_get_ext (Ptr{OCSP_ONEREQ}, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_ONEREQ_delete_ext (Ptr{OCSP_ONEREQ}, Int32) libopenssl
@c Ptr{None} OCSP_ONEREQ_get1_ext_d2i (Ptr{OCSP_ONEREQ}, Int32, Ptr{Int32}, Ptr{Int32}) libopenssl
@c Int32 OCSP_ONEREQ_add1_ext_i2d (Ptr{OCSP_ONEREQ}, Int32, Ptr{None}, Int32, Uint64) libopenssl
@c Int32 OCSP_ONEREQ_add_ext (Ptr{OCSP_ONEREQ}, Ptr{X509_EXTENSION}, Int32) libopenssl
@c Int32 OCSP_BASICRESP_get_ext_count (Ptr{OCSP_BASICRESP},) libopenssl
@c Int32 OCSP_BASICRESP_get_ext_by_NID (Ptr{OCSP_BASICRESP}, Int32, Int32) libopenssl
@c Int32 OCSP_BASICRESP_get_ext_by_OBJ (Ptr{OCSP_BASICRESP}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Int32 OCSP_BASICRESP_get_ext_by_critical (Ptr{OCSP_BASICRESP}, Int32, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_BASICRESP_get_ext (Ptr{OCSP_BASICRESP}, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_BASICRESP_delete_ext (Ptr{OCSP_BASICRESP}, Int32) libopenssl
@c Ptr{None} OCSP_BASICRESP_get1_ext_d2i (Ptr{OCSP_BASICRESP}, Int32, Ptr{Int32}, Ptr{Int32}) libopenssl
@c Int32 OCSP_BASICRESP_add1_ext_i2d (Ptr{OCSP_BASICRESP}, Int32, Ptr{None}, Int32, Uint64) libopenssl
@c Int32 OCSP_BASICRESP_add_ext (Ptr{OCSP_BASICRESP}, Ptr{X509_EXTENSION}, Int32) libopenssl
@c Int32 OCSP_SINGLERESP_get_ext_count (Ptr{OCSP_SINGLERESP},) libopenssl
@c Int32 OCSP_SINGLERESP_get_ext_by_NID (Ptr{OCSP_SINGLERESP}, Int32, Int32) libopenssl
@c Int32 OCSP_SINGLERESP_get_ext_by_OBJ (Ptr{OCSP_SINGLERESP}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Int32 OCSP_SINGLERESP_get_ext_by_critical (Ptr{OCSP_SINGLERESP}, Int32, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_SINGLERESP_get_ext (Ptr{OCSP_SINGLERESP}, Int32) libopenssl
@c Ptr{X509_EXTENSION} OCSP_SINGLERESP_delete_ext (Ptr{OCSP_SINGLERESP}, Int32) libopenssl
@c Ptr{None} OCSP_SINGLERESP_get1_ext_d2i (Ptr{OCSP_SINGLERESP}, Int32, Ptr{Int32}, Ptr{Int32}) libopenssl
@c Int32 OCSP_SINGLERESP_add1_ext_i2d (Ptr{OCSP_SINGLERESP}, Int32, Ptr{None}, Int32, Uint64) libopenssl
@c Int32 OCSP_SINGLERESP_add_ext (Ptr{OCSP_SINGLERESP}, Ptr{X509_EXTENSION}, Int32) libopenssl
@c Ptr{OCSP_SINGLERESP} OCSP_SINGLERESP_new () libopenssl
@c None OCSP_SINGLERESP_free (Ptr{OCSP_SINGLERESP},) libopenssl
@c Ptr{OCSP_SINGLERESP} d2i_OCSP_SINGLERESP (Ptr{Ptr{OCSP_SINGLERESP}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_SINGLERESP (Ptr{OCSP_SINGLERESP}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_CERTSTATUS} OCSP_CERTSTATUS_new () libopenssl
@c None OCSP_CERTSTATUS_free (Ptr{OCSP_CERTSTATUS},) libopenssl
@c Ptr{OCSP_CERTSTATUS} d2i_OCSP_CERTSTATUS (Ptr{Ptr{OCSP_CERTSTATUS}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_CERTSTATUS (Ptr{OCSP_CERTSTATUS}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_REVOKEDINFO} OCSP_REVOKEDINFO_new () libopenssl
@c None OCSP_REVOKEDINFO_free (Ptr{OCSP_REVOKEDINFO},) libopenssl
@c Ptr{OCSP_REVOKEDINFO} d2i_OCSP_REVOKEDINFO (Ptr{Ptr{OCSP_REVOKEDINFO}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_REVOKEDINFO (Ptr{OCSP_REVOKEDINFO}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_BASICRESP} OCSP_BASICRESP_new () libopenssl
@c None OCSP_BASICRESP_free (Ptr{OCSP_BASICRESP},) libopenssl
@c Ptr{OCSP_BASICRESP} d2i_OCSP_BASICRESP (Ptr{Ptr{OCSP_BASICRESP}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_BASICRESP (Ptr{OCSP_BASICRESP}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_RESPDATA} OCSP_RESPDATA_new () libopenssl
@c None OCSP_RESPDATA_free (Ptr{OCSP_RESPDATA},) libopenssl
@c Ptr{OCSP_RESPDATA} d2i_OCSP_RESPDATA (Ptr{Ptr{OCSP_RESPDATA}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_RESPDATA (Ptr{OCSP_RESPDATA}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_RESPID} OCSP_RESPID_new () libopenssl
@c None OCSP_RESPID_free (Ptr{OCSP_RESPID},) libopenssl
@c Ptr{OCSP_RESPID} d2i_OCSP_RESPID (Ptr{Ptr{OCSP_RESPID}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_RESPID (Ptr{OCSP_RESPID}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_RESPONSE} OCSP_RESPONSE_new () libopenssl
@c None OCSP_RESPONSE_free (Ptr{OCSP_RESPONSE},) libopenssl
@c Ptr{OCSP_RESPONSE} d2i_OCSP_RESPONSE (Ptr{Ptr{OCSP_RESPONSE}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_RESPONSE (Ptr{OCSP_RESPONSE}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_RESPBYTES} OCSP_RESPBYTES_new () libopenssl
@c None OCSP_RESPBYTES_free (Ptr{OCSP_RESPBYTES},) libopenssl
@c Ptr{OCSP_RESPBYTES} d2i_OCSP_RESPBYTES (Ptr{Ptr{OCSP_RESPBYTES}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_RESPBYTES (Ptr{OCSP_RESPBYTES}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_ONEREQ} OCSP_ONEREQ_new () libopenssl
@c None OCSP_ONEREQ_free (Ptr{OCSP_ONEREQ},) libopenssl
@c Ptr{OCSP_ONEREQ} d2i_OCSP_ONEREQ (Ptr{Ptr{OCSP_ONEREQ}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_ONEREQ (Ptr{OCSP_ONEREQ}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_CERTID} OCSP_CERTID_new () libopenssl
@c None OCSP_CERTID_free (Ptr{OCSP_CERTID},) libopenssl
@c Ptr{OCSP_CERTID} d2i_OCSP_CERTID (Ptr{Ptr{OCSP_CERTID}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_CERTID (Ptr{OCSP_CERTID}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_REQUEST} OCSP_REQUEST_new () libopenssl
@c None OCSP_REQUEST_free (Ptr{OCSP_REQUEST},) libopenssl
@c Ptr{OCSP_REQUEST} d2i_OCSP_REQUEST (Ptr{Ptr{OCSP_REQUEST}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_REQUEST (Ptr{OCSP_REQUEST}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_SIGNATURE} OCSP_SIGNATURE_new () libopenssl
@c None OCSP_SIGNATURE_free (Ptr{OCSP_SIGNATURE},) libopenssl
@c Ptr{OCSP_SIGNATURE} d2i_OCSP_SIGNATURE (Ptr{Ptr{OCSP_SIGNATURE}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_SIGNATURE (Ptr{OCSP_SIGNATURE}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_REQINFO} OCSP_REQINFO_new () libopenssl
@c None OCSP_REQINFO_free (Ptr{OCSP_REQINFO},) libopenssl
@c Ptr{OCSP_REQINFO} d2i_OCSP_REQINFO (Ptr{Ptr{OCSP_REQINFO}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_REQINFO (Ptr{OCSP_REQINFO}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_CRLID} OCSP_CRLID_new () libopenssl
@c None OCSP_CRLID_free (Ptr{OCSP_CRLID},) libopenssl
@c Ptr{OCSP_CRLID} d2i_OCSP_CRLID (Ptr{Ptr{OCSP_CRLID}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_CRLID (Ptr{OCSP_CRLID}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{OCSP_SERVICELOC} OCSP_SERVICELOC_new () libopenssl
@c None OCSP_SERVICELOC_free (Ptr{OCSP_SERVICELOC},) libopenssl
@c Ptr{OCSP_SERVICELOC} d2i_OCSP_SERVICELOC (Ptr{Ptr{OCSP_SERVICELOC}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_OCSP_SERVICELOC (Ptr{OCSP_SERVICELOC}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{Uint8} OCSP_response_status_str (Int64,) libopenssl
@c Ptr{Uint8} OCSP_cert_status_str (Int64,) libopenssl
@c Ptr{Uint8} OCSP_crl_reason_str (Int64,) libopenssl
@c Int32 OCSP_REQUEST_print (Ptr{BIO}, Ptr{OCSP_REQUEST}, Uint64) libopenssl
@c Int32 OCSP_RESPONSE_print (Ptr{BIO}, Ptr{OCSP_RESPONSE}, Uint64) libopenssl
@c Int32 OCSP_basic_verify (Ptr{OCSP_BASICRESP}, Ptr{STACK}, Ptr{X509_STORE}, Uint64) libopenssl
@c None ERR_load_OCSP_strings () libopenssl

