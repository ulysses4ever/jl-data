# Julia wrapper for header: /Users/dls/jl/openssl-1.0.1e/include/openssl/cms.h
# Automatically generated using Clang.jl wrap_c, version 0.0.0

@c Ptr{CMS_ContentInfo} CMS_ContentInfo_new () libopenssl
@c None CMS_ContentInfo_free (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{CMS_ContentInfo} d2i_CMS_ContentInfo (Ptr{Ptr{CMS_ContentInfo}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_CMS_ContentInfo (Ptr{CMS_ContentInfo}, Ptr{Ptr{Uint8}}) libopenssl
@c Ptr{CMS_ReceiptRequest} CMS_ReceiptRequest_new () libopenssl
@c None CMS_ReceiptRequest_free (Ptr{CMS_ReceiptRequest},) libopenssl
@c Ptr{CMS_ReceiptRequest} d2i_CMS_ReceiptRequest (Ptr{Ptr{CMS_ReceiptRequest}}, Ptr{Ptr{Uint8}}, Int64) libopenssl
@c Int32 i2d_CMS_ReceiptRequest (Ptr{CMS_ReceiptRequest}, Ptr{Ptr{Uint8}}) libopenssl
@c Int32 DECLARE_ASN1_PRINT_FUNCTION (CMS_ContentInfo,) libopenssl
@c Ptr{ASN1_OBJECT} CMS_get0_type (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{BIO} CMS_dataInit (Ptr{CMS_ContentInfo}, Ptr{BIO}) libopenssl
@c Int32 CMS_dataFinal (Ptr{CMS_ContentInfo}, Ptr{BIO}) libopenssl
@c Ptr{Ptr{ASN1_OCTET_STRING}} CMS_get0_content (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_is_detached (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_set_detached (Ptr{CMS_ContentInfo}, Int32) libopenssl
@c Int32 CMS_stream (Ptr{Ptr{Ptr{Uint8}}}, Ptr{CMS_ContentInfo}) libopenssl
@c Ptr{CMS_ContentInfo} d2i_CMS_bio (Ptr{BIO}, Ptr{Ptr{CMS_ContentInfo}}) libopenssl
@c Int32 i2d_CMS_bio (Ptr{BIO}, Ptr{CMS_ContentInfo}) libopenssl
@c Ptr{BIO} BIO_new_CMS (Ptr{BIO}, Ptr{CMS_ContentInfo}) libopenssl
@c Int32 i2d_CMS_bio_stream (Ptr{BIO}, Ptr{CMS_ContentInfo}, Ptr{BIO}, Int32) libopenssl
@c Int32 PEM_write_bio_CMS_stream (Ptr{BIO}, Ptr{CMS_ContentInfo}, Ptr{BIO}, Int32) libopenssl
@c Ptr{CMS_ContentInfo} SMIME_read_CMS (Ptr{BIO}, Ptr{Ptr{BIO}}) libopenssl
@c Int32 SMIME_write_CMS (Ptr{BIO}, Ptr{CMS_ContentInfo}, Ptr{BIO}, Int32) libopenssl
@c Int32 CMS_final (Ptr{CMS_ContentInfo}, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_sign (Ptr{X509}, Ptr{EVP_PKEY}, Ptr{STACK}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_sign_receipt (Ptr{CMS_SignerInfo}, Ptr{X509}, Ptr{EVP_PKEY}, Ptr{STACK}, Uint32) libopenssl
@c Int32 CMS_data (Ptr{CMS_ContentInfo}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_data_create (Ptr{BIO}, Uint32) libopenssl
@c Int32 CMS_digest_verify (Ptr{CMS_ContentInfo}, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_digest_create (Ptr{BIO}, Ptr{EVP_MD}, Uint32) libopenssl
@c Int32 CMS_EncryptedData_decrypt (Ptr{CMS_ContentInfo}, Ptr{Uint8}, Csize_t, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_EncryptedData_encrypt (Ptr{BIO}, Ptr{EVP_CIPHER}, Ptr{Uint8}, Csize_t, Uint32) libopenssl
@c Int32 CMS_EncryptedData_set1_key (Ptr{CMS_ContentInfo}, Ptr{EVP_CIPHER}, Ptr{Uint8}, Csize_t) libopenssl
@c Int32 CMS_verify (Ptr{CMS_ContentInfo}, Ptr{STACK}, Ptr{X509_STORE}, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Int32 CMS_verify_receipt (Ptr{CMS_ContentInfo}, Ptr{CMS_ContentInfo}, Ptr{STACK}, Ptr{X509_STORE}, Uint32) libopenssl
@c Ptr{STACK} CMS_get0_signers (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{CMS_ContentInfo} CMS_encrypt (Ptr{STACK}, Ptr{BIO}, Ptr{EVP_CIPHER}, Uint32) libopenssl
@c Int32 CMS_decrypt (Ptr{CMS_ContentInfo}, Ptr{EVP_PKEY}, Ptr{X509}, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Int32 CMS_decrypt_set1_pkey (Ptr{CMS_ContentInfo}, Ptr{EVP_PKEY}, Ptr{X509}) libopenssl
@c Int32 CMS_decrypt_set1_key (Ptr{CMS_ContentInfo}, Ptr{Uint8}, Csize_t, Ptr{Uint8}, Csize_t) libopenssl
@c Int32 CMS_decrypt_set1_password (Ptr{CMS_ContentInfo}, Ptr{Uint8}, Int32) libopenssl
@c Ptr{STACK} CMS_get0_RecipientInfos (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_RecipientInfo_type (Ptr{CMS_RecipientInfo},) libopenssl
@c Ptr{CMS_ContentInfo} CMS_EnvelopedData_create (Ptr{EVP_CIPHER},) libopenssl
@c Ptr{CMS_RecipientInfo} CMS_add1_recipient_cert (Ptr{CMS_ContentInfo}, Ptr{X509}, Uint32) libopenssl
@c Int32 CMS_RecipientInfo_set0_pkey (Ptr{CMS_RecipientInfo}, Ptr{EVP_PKEY}) libopenssl
@c Int32 CMS_RecipientInfo_ktri_cert_cmp (Ptr{CMS_RecipientInfo}, Ptr{X509}) libopenssl
@c Int32 CMS_RecipientInfo_ktri_get0_algs (Ptr{CMS_RecipientInfo}, Ptr{Ptr{EVP_PKEY}}, Ptr{Ptr{X509}}, Ptr{Ptr{X509_ALGOR}}) libopenssl
@c Int32 CMS_RecipientInfo_ktri_get0_signer_id (Ptr{CMS_RecipientInfo}, Ptr{Ptr{ASN1_OCTET_STRING}}, Ptr{Ptr{X509_NAME}}, Ptr{Ptr{ASN1_INTEGER}}) libopenssl
@c Ptr{CMS_RecipientInfo} CMS_add0_recipient_key (Ptr{CMS_ContentInfo}, Int32, Ptr{Uint8}, Csize_t, Ptr{Uint8}, Csize_t, Ptr{ASN1_GENERALIZEDTIME}, Ptr{ASN1_OBJECT}, Ptr{ASN1_TYPE}) libopenssl
@c Int32 CMS_RecipientInfo_kekri_get0_id (Ptr{CMS_RecipientInfo}, Ptr{Ptr{X509_ALGOR}}, Ptr{Ptr{ASN1_OCTET_STRING}}, Ptr{Ptr{ASN1_GENERALIZEDTIME}}, Ptr{Ptr{ASN1_OBJECT}}, Ptr{Ptr{ASN1_TYPE}}) libopenssl
@c Int32 CMS_RecipientInfo_set0_key (Ptr{CMS_RecipientInfo}, Ptr{Uint8}, Csize_t) libopenssl
@c Int32 CMS_RecipientInfo_kekri_id_cmp (Ptr{CMS_RecipientInfo}, Ptr{Uint8}, Csize_t) libopenssl
@c Int32 CMS_RecipientInfo_set0_password (Ptr{CMS_RecipientInfo}, Ptr{Uint8}, Int32) libopenssl
@c Ptr{CMS_RecipientInfo} CMS_add0_recipient_password (Ptr{CMS_ContentInfo}, Int32, Int32, Int32, Ptr{Uint8}, Int32, Ptr{EVP_CIPHER}) libopenssl
@c Int32 CMS_RecipientInfo_decrypt (Ptr{CMS_ContentInfo}, Ptr{CMS_RecipientInfo}) libopenssl
@c Int32 CMS_uncompress (Ptr{CMS_ContentInfo}, Ptr{BIO}, Ptr{BIO}, Uint32) libopenssl
@c Ptr{CMS_ContentInfo} CMS_compress (Ptr{BIO}, Int32, Uint32) libopenssl
@c Int32 CMS_set1_eContentType (Ptr{CMS_ContentInfo}, Ptr{ASN1_OBJECT}) libopenssl
@c Ptr{ASN1_OBJECT} CMS_get0_eContentType (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{CMS_CertificateChoices} CMS_add0_CertificateChoices (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_add0_cert (Ptr{CMS_ContentInfo}, Ptr{X509}) libopenssl
@c Int32 CMS_add1_cert (Ptr{CMS_ContentInfo}, Ptr{X509}) libopenssl
@c Ptr{STACK} CMS_get1_certs (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{CMS_RevocationInfoChoice} CMS_add0_RevocationInfoChoice (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_add0_crl (Ptr{CMS_ContentInfo}, Ptr{X509_CRL}) libopenssl
@c Int32 CMS_add1_crl (Ptr{CMS_ContentInfo}, Ptr{X509_CRL}) libopenssl
@c Ptr{STACK} CMS_get1_crls (Ptr{CMS_ContentInfo},) libopenssl
@c Int32 CMS_SignedData_init (Ptr{CMS_ContentInfo},) libopenssl
@c Ptr{CMS_SignerInfo} CMS_add1_signer (Ptr{CMS_ContentInfo}, Ptr{X509}, Ptr{EVP_PKEY}, Ptr{EVP_MD}, Uint32) libopenssl
@c Ptr{STACK} CMS_get0_SignerInfos (Ptr{CMS_ContentInfo},) libopenssl
@c None CMS_SignerInfo_set1_signer_cert (Ptr{CMS_SignerInfo}, Ptr{X509}) libopenssl
@c Int32 CMS_SignerInfo_get0_signer_id (Ptr{CMS_SignerInfo}, Ptr{Ptr{ASN1_OCTET_STRING}}, Ptr{Ptr{X509_NAME}}, Ptr{Ptr{ASN1_INTEGER}}) libopenssl
@c Int32 CMS_SignerInfo_cert_cmp (Ptr{CMS_SignerInfo}, Ptr{X509}) libopenssl
@c Int32 CMS_set1_signers_certs (Ptr{CMS_ContentInfo}, Ptr{STACK}, Uint32) libopenssl
@c None CMS_SignerInfo_get0_algs (Ptr{CMS_SignerInfo}, Ptr{Ptr{EVP_PKEY}}, Ptr{Ptr{X509}}, Ptr{Ptr{X509_ALGOR}}, Ptr{Ptr{X509_ALGOR}}) libopenssl
@c Int32 CMS_SignerInfo_sign (Ptr{CMS_SignerInfo},) libopenssl
@c Int32 CMS_SignerInfo_verify (Ptr{CMS_SignerInfo},) libopenssl
@c Int32 CMS_SignerInfo_verify_content (Ptr{CMS_SignerInfo}, Ptr{BIO}) libopenssl
@c Int32 CMS_add_smimecap (Ptr{CMS_SignerInfo}, Ptr{STACK}) libopenssl
@c Int32 CMS_add_simple_smimecap (Ptr{Ptr{STACK}}, Int32, Int32) libopenssl
@c Int32 CMS_add_standard_smimecap (Ptr{Ptr{STACK}},) libopenssl
@c Int32 CMS_signed_get_attr_count (Ptr{CMS_SignerInfo},) libopenssl
@c Int32 CMS_signed_get_attr_by_NID (Ptr{CMS_SignerInfo}, Int32, Int32) libopenssl
@c Int32 CMS_signed_get_attr_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Ptr{X509_ATTRIBUTE} CMS_signed_get_attr (Ptr{CMS_SignerInfo}, Int32) libopenssl
@c Ptr{X509_ATTRIBUTE} CMS_signed_delete_attr (Ptr{CMS_SignerInfo}, Int32) libopenssl
@c Int32 CMS_signed_add1_attr (Ptr{CMS_SignerInfo}, Ptr{X509_ATTRIBUTE}) libopenssl
@c Int32 CMS_signed_add1_attr_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32, Ptr{None}, Int32) libopenssl
@c Int32 CMS_signed_add1_attr_by_NID (Ptr{CMS_SignerInfo}, Int32, Int32, Ptr{None}, Int32) libopenssl
@c Int32 CMS_signed_add1_attr_by_txt (Ptr{CMS_SignerInfo}, Ptr{Uint8}, Int32, Ptr{None}, Int32) libopenssl
@c Ptr{None} CMS_signed_get0_data_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32, Int32) libopenssl
@c Int32 CMS_unsigned_get_attr_count (Ptr{CMS_SignerInfo},) libopenssl
@c Int32 CMS_unsigned_get_attr_by_NID (Ptr{CMS_SignerInfo}, Int32, Int32) libopenssl
@c Int32 CMS_unsigned_get_attr_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32) libopenssl
@c Ptr{X509_ATTRIBUTE} CMS_unsigned_get_attr (Ptr{CMS_SignerInfo}, Int32) libopenssl
@c Ptr{X509_ATTRIBUTE} CMS_unsigned_delete_attr (Ptr{CMS_SignerInfo}, Int32) libopenssl
@c Int32 CMS_unsigned_add1_attr (Ptr{CMS_SignerInfo}, Ptr{X509_ATTRIBUTE}) libopenssl
@c Int32 CMS_unsigned_add1_attr_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32, Ptr{None}, Int32) libopenssl
@c Int32 CMS_unsigned_add1_attr_by_NID (Ptr{CMS_SignerInfo}, Int32, Int32, Ptr{None}, Int32) libopenssl
@c Int32 CMS_unsigned_add1_attr_by_txt (Ptr{CMS_SignerInfo}, Ptr{Uint8}, Int32, Ptr{None}, Int32) libopenssl
@c Ptr{None} CMS_unsigned_get0_data_by_OBJ (Ptr{CMS_SignerInfo}, Ptr{ASN1_OBJECT}, Int32, Int32) libopenssl
@c None ERR_load_CMS_strings () libopenssl

