macro c(ret_type, func, arg_types, lib)
  local args_in = Any[ symbol(string('a',x)) for x in 1:length(arg_types.args) ]
  quote
    $(esc(func))($(args_in...)) = ccall( ($(string(func)), $(Expr(:quote, lib)) ), $ret_type, $arg_types, $(args_in...) )
  end
end

macro ctypedef(fake_t,real_t)
  quote
    typealias $fake_t $real_t
  end
end

@ctypedef BIT_STRING_BITNAME BIT_STRING_BITNAME_st
type aes_key_st
  rd_key::Void
  rounds::Int32
end
@ctypedef AES_KEY aes_key_st
type asn1_ctx_st
  p::Ptr{Uint8}
  eos::Int32
  error::Int32
  inf::Int32
  tag::Int32
  xclass::Int32
  slen::Int64
  max::Ptr{Uint8}
  q::Ptr{Uint8}
  pp::Ptr{Ptr{Uint8}}
  line::Int32
end
@ctypedef ASN1_CTX asn1_ctx_st
type asn1_const_ctx_st
  p::Ptr{Uint8}
  eos::Int32
  error::Int32
  inf::Int32
  tag::Int32
  xclass::Int32
  slen::Int64
  max::Ptr{Uint8}
  q::Ptr{Uint8}
  pp::Ptr{Ptr{Uint8}}
  line::Int32
end
@ctypedef ASN1_const_CTX asn1_const_ctx_st
type asn1_object_st
  sn::Ptr{Uint8}
  ln::Ptr{Uint8}
  nid::Int32
  length::Int32
  data::Ptr{Uint8}
  flags::Int32
end
@ctypedef ASN1_OBJECT asn1_object_st
type asn1_string_st
  length::Int32
  _type::Int32
  data::Ptr{Uint8}
  flags::Int64
end
type ASN1_ENCODING_st
  enc::Ptr{Uint8}
  len::Int64
  modified::Int32
end
@ctypedef ASN1_ENCODING ASN1_ENCODING_st
type asn1_string_table_st
  nid::Int32
  minsize::Int64
  maxsize::Int64
  mask::Uint64
  flags::Uint64
end
@ctypedef ASN1_STRING_TABLE asn1_string_table_st
@ctypedef ASN1_TEMPLATE ASN1_TEMPLATE_st
@ctypedef ASN1_TLC ASN1_TLC_st
@ctypedef ASN1_VALUE ASN1_VALUE_st
@ctypedef d2i_of_void Void
@ctypedef i2d_of_void Void
@ctypedef ASN1_ITEM_EXP Int32
type asn1_type_st
  _type::Int32
  value::
end
@ctypedef ASN1_TYPE asn1_type_st
@ctypedef ASN1_SEQUENCE_ANY STACK
type NETSCAPE_X509_st
  header::Ptr{ASN1_OCTET_STRING}
  cert::Ptr{X509}
end
@ctypedef NETSCAPE_X509 NETSCAPE_X509_st
type BIT_STRING_BITNAME_st
  bitnum::Int32
  lname::Ptr{Uint8}
  sname::Ptr{Uint8}
end
@ctypedef ASN1_ADB_TABLE ASN1_ADB_TABLE_st
@ctypedef ASN1_ADB ASN1_ADB_st
type ASN1_ITEM_st
  itype::Uint8
  utype::Int64
  templates::Ptr{ASN1_TEMPLATE}
  tcount::Int64
  funcs::Ptr{None}
  size::Int64
  sname::Ptr{Uint8}
end
@ctypedef ASN1_new_func Void
@ctypedef ASN1_free_func Void
@ctypedef ASN1_d2i_func Void
@ctypedef ASN1_i2d_func Void
@ctypedef ASN1_ex_d2i Void
@ctypedef ASN1_ex_i2d Void
@ctypedef ASN1_ex_new_func Void
@ctypedef ASN1_ex_free_func Void
@ctypedef ASN1_ex_print_func Void
@ctypedef ASN1_primitive_i2c Void
@ctypedef ASN1_primitive_c2i Void
@ctypedef ASN1_primitive_print Void
type ASN1_COMPAT_FUNCS_st
  asn1_new::Ptr{ASN1_new_func}
  asn1_free::Ptr{ASN1_free_func}
  asn1_d2i::Ptr{ASN1_d2i_func}
  asn1_i2d::Ptr{ASN1_i2d_func}
end
@ctypedef ASN1_COMPAT_FUNCS ASN1_COMPAT_FUNCS_st
type ASN1_EXTERN_FUNCS_st
  app_data::Ptr{None}
  asn1_ex_new::Ptr{ASN1_ex_new_func}
  asn1_ex_free::Ptr{ASN1_ex_free_func}
  asn1_ex_clear::Ptr{ASN1_ex_free_func}
  asn1_ex_d2i::Ptr{ASN1_ex_d2i}
  asn1_ex_i2d::Ptr{ASN1_ex_i2d}
  asn1_ex_print::Ptr{ASN1_ex_print_func}
end
@ctypedef ASN1_EXTERN_FUNCS ASN1_EXTERN_FUNCS_st
type ASN1_PRIMITIVE_FUNCS_st
  app_data::Ptr{None}
  flags::Uint64
  prim_new::Ptr{ASN1_ex_new_func}
  prim_free::Ptr{ASN1_ex_free_func}
  prim_clear::Ptr{ASN1_ex_free_func}
  prim_c2i::Ptr{ASN1_primitive_c2i}
  prim_i2c::Ptr{ASN1_primitive_i2c}
  prim_print::Ptr{ASN1_primitive_print}
end
@ctypedef ASN1_PRIMITIVE_FUNCS ASN1_PRIMITIVE_FUNCS_st
@ctypedef ASN1_aux_cb Void
type ASN1_AUX_st
  app_data::Ptr{None}
  flags::Int32
  ref_offset::Int32
  ref_lock::Int32
  asn1_cb::Ptr{ASN1_aux_cb}
  enc_offset::Int32
end
@ctypedef ASN1_AUX ASN1_AUX_st
type ASN1_PRINT_ARG_st
  out::Ptr{BIO}
  indent::Int32
  pctx::Ptr{Int32}
end
@ctypedef ASN1_PRINT_ARG ASN1_PRINT_ARG_st
type ASN1_STREAM_ARG_st
  out::Ptr{BIO}
  ndef_bio::Ptr{BIO}
  boundary::Ptr{Ptr{Uint8}}
end
@ctypedef ASN1_STREAM_ARG ASN1_STREAM_ARG_st
@ctypedef BIO bio_st
@ctypedef bio_info_cb Void
type bio_method_st
  _type::Int32
  name::Ptr{Uint8}
  bwrite::Ptr{Void}
  bread::Ptr{Void}
  bputs::Ptr{Void}
  bgets::Ptr{Void}
  ctrl::Ptr{Void}
  create::Ptr{Void}
  destroy::Ptr{Void}
  callback_ctrl::Ptr{Void}
end
@ctypedef BIO_METHOD bio_method_st
type bio_st
  method::Ptr{BIO_METHOD}
  callback::Ptr{Void}
  cb_arg::Ptr{Uint8}
  init::Int32
  shutdown::Int32
  flags::Int32
  retry_reason::Int32
  num::Int32
  ptr::Ptr{None}
  next_bio::Ptr{Void}
  prev_bio::Ptr{Void}
  references::Int32
  num_read::Uint64
  num_write::Uint64
  ex_data::CRYPTO_EX_DATA
end
type bio_f_buffer_ctx_struct
  ibuf_size::Int32
  obuf_size::Int32
  ibuf::Ptr{Uint8}
  ibuf_len::Int32
  ibuf_off::Int32
  obuf::Ptr{Uint8}
  obuf_len::Int32
  obuf_off::Int32
end
@ctypedef BIO_F_BUFFER_CTX bio_f_buffer_ctx_struct
@ctypedef asn1_ps_func Void
type bio_dgram_sctp_sndinfo
  snd_sid::Int32
  snd_flags::Int32
  snd_ppid::Int32
  snd_context::Int32
end
type bio_dgram_sctp_rcvinfo
  rcv_sid::Int32
  rcv_ssn::Int32
  rcv_flags::Int32
  rcv_ppid::Int32
  rcv_tsn::Int32
  rcv_cumtsn::Int32
  rcv_context::Int32
end
type bio_dgram_sctp_prinfo
  pr_policy::Int32
  pr_value::Int32
end
type bf_key_st
  P::Void
  S::Void
end
@ctypedef BF_KEY bf_key_st
type bignum_st
  d::Ptr{Uint64}
  top::Int32
  dmax::Int32
  neg::Int32
  flags::Int32
end
type bn_mont_ctx_st
  ri::Int32
  RR::BIGNUM
  N::BIGNUM
  Ni::BIGNUM
  n0::Void
  flags::Int32
end
type bn_recp_ctx_st
  N::BIGNUM
  Nr::BIGNUM
  num_bits::Int32
  shift::Int32
  flags::Int32
end
type bn_gencb_st
  ver::Uint32
  arg::Ptr{None}
  cb::
end
type buf_mem_st
  length::Csize_t
  data::Ptr{Uint8}
  max::Csize_t
end
@ctypedef KEY_TABLE_TYPE Void
type camellia_key_st
  u::
  grand_rounds::Int32
end
@ctypedef CAMELLIA_KEY camellia_key_st
type cast_key_st
  data::Void
  short_key::Int32
end
@ctypedef CAST_KEY cast_key_st
@ctypedef CMAC_CTX CMAC_CTX_st
@ctypedef CMS_ContentInfo CMS_ContentInfo_st
@ctypedef CMS_SignerInfo CMS_SignerInfo_st
@ctypedef CMS_RevocationInfoChoice CMS_RevocationInfoChoice_st
@ctypedef CMS_RecipientInfo CMS_RecipientInfo_st
@ctypedef CMS_ReceiptRequest CMS_ReceiptRequest_st
@ctypedef CMS_Receipt CMS_Receipt_st
@ctypedef COMP_CTX comp_ctx_st
type comp_method_st
  _type::Int32
  name::Ptr{Uint8}
  init::Ptr{Void}
  finish::Ptr{Void}
  compress::Ptr{Void}
  expand::Ptr{Void}
  ctrl::Ptr{Void}
  callback_ctrl::Ptr{Void}
end
@ctypedef COMP_METHOD comp_method_st
type CONF_VALUE
  section::Ptr{Uint8}
  name::Ptr{Uint8}
  value::Ptr{Uint8}
end
@ctypedef CONF_METHOD conf_method_st
@ctypedef CONF_IMODULE conf_imodule_st
@ctypedef CONF_MODULE conf_module_st
@ctypedef conf_init_func Void
@ctypedef conf_finish_func Void
type openssl_item_st
  code::Int32
  value::Ptr{None}
  value_size::Csize_t
  value_length::Ptr{Csize_t}
end
@ctypedef OPENSSL_ITEM openssl_item_st
type CRYPTO_dynlock
  references::Int32
  data::Ptr{Void}
end
@ctypedef BIO_dummy bio_st
type crypto_ex_data_st
  sk::Ptr{STACK}
  dummy::Int32
end
type crypto_ex_data_func_st
  argl::Int64
  argp::Ptr{None}
  new_func::Ptr{CRYPTO_EX_new}
  free_func::Ptr{CRYPTO_EX_free}
  dup_func::Ptr{CRYPTO_EX_dup}
end
@ctypedef CRYPTO_EX_DATA_FUNCS crypto_ex_data_func_st
@ctypedef CRYPTO_EX_DATA_IMPL st_CRYPTO_EX_DATA_IMPL
type crypto_threadid_st
  ptr::Ptr{None}
  val::Uint64
end
@ctypedef CRYPTO_THREADID crypto_threadid_st
@ctypedef CRYPTO_MEM_LEAK_CB Void
@ctypedef DES_cblock Void
@ctypedef const_DES_cblock Void
type DES_ks
  ks::Void
end
@ctypedef DES_key_schedule DES_ks
@ctypedef _ossl_old_des_cblock Void
type _ossl_old_des_ks_struct
  ks::
end
@ctypedef _ossl_old_des_key_schedule Void
type dh_method
  name::Ptr{Uint8}
  generate_key::Ptr{Void}
  compute_key::Ptr{Void}
  bn_mod_exp::Ptr{Void}
  init::Ptr{Void}
  finish::Ptr{Void}
  flags::Int32
  app_data::Ptr{Uint8}
  generate_params::Ptr{Void}
end
type dh_st
  pad::Int32
  version::Int32
  p::Ptr{BIGNUM}
  g::Ptr{BIGNUM}
  length::Int64
  pub_key::Ptr{BIGNUM}
  priv_key::Ptr{BIGNUM}
  flags::Int32
  method_mont_p::Ptr{BN_MONT_CTX}
  q::Ptr{BIGNUM}
  j::Ptr{BIGNUM}
  seed::Ptr{Uint8}
  seedlen::Int32
  counter::Ptr{BIGNUM}
  references::Int32
  ex_data::CRYPTO_EX_DATA
  meth::Ptr{DH_METHOD}
  engine::Ptr{ENGINE}
end
type DSA_SIG_st
  r::Ptr{BIGNUM}
  s::Ptr{BIGNUM}
end
@ctypedef DSA_SIG DSA_SIG_st
type dsa_method
  name::Ptr{Uint8}
  dsa_do_sign::Ptr{Void}
  dsa_sign_setup::Ptr{Void}
  dsa_do_verify::Ptr{Void}
  dsa_mod_exp::Ptr{Void}
  bn_mod_exp::Ptr{Void}
  init::Ptr{Void}
  finish::Ptr{Void}
  flags::Int32
  app_data::Ptr{Uint8}
  dsa_paramgen::Ptr{Void}
  dsa_keygen::Ptr{Void}
end
type dsa_st
  pad::Int32
  version::Int64
  write_params::Int32
  p::Ptr{BIGNUM}
  q::Ptr{BIGNUM}
  g::Ptr{BIGNUM}
  pub_key::Ptr{BIGNUM}
  priv_key::Ptr{BIGNUM}
  kinv::Ptr{BIGNUM}
  r::Ptr{BIGNUM}
  flags::Int32
  method_mont_p::Ptr{BN_MONT_CTX}
  references::Int32
  ex_data::CRYPTO_EX_DATA
  meth::Ptr{DSA_METHOD}
  engine::Ptr{ENGINE}
end
@ctypedef DSO_FUNC_TYPE Ptr{Void}
@ctypedef DSO dso_st
@ctypedef DSO_NAME_CONVERTER_FUNC Ptr{Void}
@ctypedef DSO_MERGER_FUNC Ptr{Void}
type dso_meth_st
  name::Ptr{Uint8}
  dso_load::Ptr{Void}
  dso_unload::Ptr{Void}
  dso_bind_var::Ptr{Void}
  dso_bind_func::Ptr{Void}
  dso_ctrl::Ptr{Void}
  dso_name_converter::DSO_NAME_CONVERTER_FUNC
  dso_merger::DSO_MERGER_FUNC
  init::Ptr{Void}
  finish::Ptr{Void}
  pathbyaddr::Ptr{Void}
  globallookup::Ptr{Void}
end
@ctypedef DSO_METHOD dso_meth_st
type dtls1_bitmap_st
  map::Uint64
  max_seq_num::Void
end
@ctypedef DTLS1_BITMAP dtls1_bitmap_st
type dtls1_retransmit_state
  enc_write_ctx::Ptr{EVP_CIPHER_CTX}
  write_hash::Ptr{EVP_MD_CTX}
  compress::Ptr{Int32}
  session::Ptr{Int32}
  epoch::Uint16
end
type hm_header_st
  _type::Uint8
  msg_len::Uint64
  seq::Uint16
  frag_off::Uint64
  frag_len::Uint64
  is_ccs::Uint32
  saved_retransmit_state::dtls1_retransmit_state
end
type ccs_header_st
  _type::Uint8
  seq::Uint16
end
type dtls1_timeout_st
  read_timeouts::Uint32
  write_timeouts::Uint32
  num_alerts::Uint32
end
type record_pqueue_st
  epoch::Uint16
  q::pqueue
end
@ctypedef record_pqueue record_pqueue_st
type hm_fragment_st
  msg_header::hm_header_st
  fragment::Ptr{Uint8}
  reassembly::Ptr{Uint8}
end
@ctypedef hm_fragment hm_fragment_st
type dtls1_state_st
  send_cookie::Uint32
  cookie::Void
  rcvd_cookie::Void
  cookie_len::Uint32
  r_epoch::Uint16
  w_epoch::Uint16
  bitmap::DTLS1_BITMAP
  next_bitmap::DTLS1_BITMAP
  handshake_write_seq::Uint16
  next_handshake_write_seq::Uint16
  handshake_read_seq::Uint16
  last_write_sequence::Void
  unprocessed_rcds::record_pqueue
  processed_rcds::record_pqueue
  buffered_messages::pqueue
  sent_messages::pqueue
  buffered_app_data::record_pqueue
  listen::Uint32
  mtu::Uint32
  w_msg_hdr::hm_header_st
  r_msg_hdr::hm_header_st
  timeout::dtls1_timeout_st
  next_timeout::timeval
  timeout_duration::Uint16
  alert_fragment::Void
  alert_fragment_len::Uint32
  handshake_fragment::Void
  handshake_fragment_len::Uint32
  retransmitting::Uint32
  change_cipher_spec_ok::Uint32
  next_state::Int32
  shutdown_received::Int32
end
@ctypedef DTLS1_STATE dtls1_state_st
type dtls1_record_data_st
  packet::Ptr{Uint8}
  packet_length::Uint32
  rbuf::Int32
  rrec::Int32
  recordinfo::bio_dgram_sctp_rcvinfo
end
@ctypedef DTLS1_RECORD_DATA dtls1_record_data_st
# enum point_conversion_form_t
const POINT_CONVERSION_COMPRESSED = 2
const POINT_CONVERSION_UNCOMPRESSED = 4
const POINT_CONVERSION_HYBRID = 6
# end
@ctypedef point_conversion_form_t Int32
@ctypedef EC_METHOD ec_method_st
@ctypedef EC_GROUP ec_group_st
@ctypedef EC_POINT ec_point_st
type EC_builtin_curve
  nid::Int32
  comment::Ptr{Uint8}
end
@ctypedef ECPKPARAMETERS ecpk_parameters_st
@ctypedef EC_KEY ec_key_st
type ECDSA_SIG_st
  r::Ptr{BIGNUM}
  s::Ptr{BIGNUM}
end
@ctypedef ECDSA_SIG ECDSA_SIG_st
type ENGINE_CMD_DEFN_st
  cmd_num::Uint32
  cmd_name::Ptr{Uint8}
  cmd_desc::Ptr{Uint8}
  cmd_flags::Uint32
end
@ctypedef ENGINE_CMD_DEFN ENGINE_CMD_DEFN_st
@ctypedef ENGINE_GEN_FUNC_PTR Ptr{Void}
@ctypedef ENGINE_GEN_INT_FUNC_PTR Ptr{Void}
@ctypedef ENGINE_CTRL_FUNC_PTR Ptr{Void}
@ctypedef ENGINE_LOAD_KEY_PTR Ptr{Void}
@ctypedef ENGINE_SSL_CLIENT_CERT_PTR Ptr{Void}
@ctypedef ENGINE_CIPHERS_PTR Ptr{Void}
@ctypedef ENGINE_DIGESTS_PTR Ptr{Void}
@ctypedef ENGINE_PKEY_METHS_PTR Ptr{Void}
@ctypedef ENGINE_PKEY_ASN1_METHS_PTR Ptr{Void}
@ctypedef dyn_MEM_malloc_cb Ptr{Void}
@ctypedef dyn_MEM_realloc_cb Ptr{Void}
@ctypedef dyn_MEM_free_cb Ptr{Void}
type st_dynamic_MEM_fns
  malloc_cb::dyn_MEM_malloc_cb
  realloc_cb::dyn_MEM_realloc_cb
  free_cb::dyn_MEM_free_cb
end
@ctypedef dynamic_MEM_fns st_dynamic_MEM_fns
@ctypedef dyn_lock_locking_cb Ptr{Void}
@ctypedef dyn_lock_add_lock_cb Ptr{Void}
@ctypedef dyn_dynlock_create_cb Ptr{Void}
@ctypedef dyn_dynlock_lock_cb Ptr{Void}
@ctypedef dyn_dynlock_destroy_cb Ptr{Void}
type st_dynamic_LOCK_fns
  lock_locking_cb::dyn_lock_locking_cb
  lock_add_lock_cb::dyn_lock_add_lock_cb
  dynlock_create_cb::dyn_dynlock_create_cb
  dynlock_lock_cb::dyn_dynlock_lock_cb
  dynlock_destroy_cb::dyn_dynlock_destroy_cb
end
@ctypedef dynamic_LOCK_fns st_dynamic_LOCK_fns
type st_dynamic_fns
  static_state::Ptr{None}
  err_fns::Ptr{ERR_FNS}
  ex_data_fns::Ptr{CRYPTO_EX_DATA_IMPL}
  mem_fns::dynamic_MEM_fns
  lock_fns::dynamic_LOCK_fns
end
@ctypedef dynamic_fns st_dynamic_fns
@ctypedef dynamic_v_check_fn Ptr{Void}
@ctypedef dynamic_bind_engine Ptr{Void}
type err_state_st
  tid::Int32
  err_flags::Void
  err_buffer::Void
  err_data::Void
  err_data_flags::Void
  err_file::Void
  err_line::Void
  top::Int32
  bottom::Int32
end
@ctypedef ERR_STATE err_state_st
type ERR_string_data_st
  error::Uint64
  string::Ptr{Uint8}
end
@ctypedef ERR_STRING_DATA ERR_string_data_st
type evp_pkey_st
  _type::Int32
  save_type::Int32
  references::Int32
  ameth::Ptr{Int32}
  engine::Ptr{ENGINE}
  pkey::
  save_parameters::Int32
  attributes::Ptr{STACK}
end
type env_md_st
  _type::Int32
  pkey_type::Int32
  md_size::Int32
  flags::Uint64
  init::Ptr{Void}
  update::Ptr{Void}
  final::Ptr{Void}
  copy::Ptr{Void}
  cleanup::Ptr{Void}
  sign::Ptr{Void}
  verify::Ptr{Void}
  required_pkey_type::Void
  block_size::Int32
  ctx_size::Int32
  md_ctrl::Ptr{Void}
end
@ctypedef evp_sign_method Void
@ctypedef evp_verify_method Void
type env_md_ctx_st
  digest::Ptr{EVP_MD}
  engine::Ptr{ENGINE}
  flags::Uint64
  md_data::Ptr{None}
  pctx::Ptr{Int32}
  update::Ptr{Void}
end
type evp_cipher_st
  nid::Int32
  block_size::Int32
  key_len::Int32
  iv_len::Int32
  flags::Uint64
  init::Ptr{Void}
  do_cipher::Ptr{Void}
  cleanup::Ptr{Void}
  ctx_size::Int32
  set_asn1_parameters::Ptr{Void}
  get_asn1_parameters::Ptr{Void}
  ctrl::Ptr{Void}
  app_data::Ptr{None}
end
type evp_cipher_info_st
  cipher::Ptr{EVP_CIPHER}
  iv::Void
end
@ctypedef EVP_CIPHER_INFO evp_cipher_info_st
type evp_cipher_ctx_st
  cipher::Ptr{EVP_CIPHER}
  engine::Ptr{ENGINE}
  encrypt::Int32
  buf_len::Int32
  oiv::Void
  iv::Void
  buf::Void
  num::Int32
  app_data::Ptr{None}
  key_len::Int32
  flags::Uint64
  cipher_data::Ptr{None}
  final_used::Int32
  block_mask::Int32
  final::Void
end
type evp_Encode_Ctx_st
  num::Int32
  length::Int32
  enc_data::Void
  line_num::Int32
  expect_nl::Int32
end
@ctypedef EVP_ENCODE_CTX evp_Encode_Ctx_st
@ctypedef EVP_PBE_KEYGEN Void
@ctypedef EVP_PKEY_gen_cb Void
type hmac_ctx_st
  md::Ptr{EVP_MD}
  md_ctx::EVP_MD_CTX
  i_ctx::EVP_MD_CTX
  o_ctx::EVP_MD_CTX
  key_length::Uint32
  key::Void
end
@ctypedef HMAC_CTX hmac_ctx_st
type idea_key_st
  data::Void
end
@ctypedef IDEA_KEY_SCHEDULE idea_key_st
type krb5_encdata_st
  etype::Ptr{Int32}
  kvno::Ptr{Int32}
  cipher::Ptr{Int32}
end
@ctypedef KRB5_ENCDATA krb5_encdata_st
type krb5_princname_st
  nametype::Ptr{Int32}
  namestring::Ptr{STACK}
end
@ctypedef KRB5_PRINCNAME krb5_princname_st
type krb5_tktbody_st
  tktvno::Ptr{Int32}
  realm::Ptr{Int32}
  sname::Ptr{KRB5_PRINCNAME}
  encdata::Ptr{KRB5_ENCDATA}
end
@ctypedef KRB5_TKTBODY krb5_tktbody_st
@ctypedef KRB5_TICKET STACK
type krb5_ap_req_st
  pvno::Ptr{Int32}
  msgtype::Ptr{Int32}
  apoptions::Ptr{Int32}
  ticket::Ptr{KRB5_TICKET}
  authenticator::Ptr{KRB5_ENCDATA}
end
@ctypedef KRB5_APREQBODY krb5_ap_req_st
@ctypedef KRB5_APREQ STACK
type krb5_checksum_st
  ctype::Ptr{Int32}
  checksum::Ptr{Int32}
end
@ctypedef KRB5_CHECKSUM krb5_checksum_st
type krb5_encryptionkey_st
  ktype::Ptr{Int32}
  keyvalue::Ptr{Int32}
end
@ctypedef KRB5_ENCKEY krb5_encryptionkey_st
type krb5_authorization_st
  adtype::Ptr{Int32}
  addata::Ptr{Int32}
end
@ctypedef KRB5_AUTHDATA krb5_authorization_st
type krb5_authenticator_st
  avno::Ptr{Int32}
  crealm::Ptr{Int32}
  cname::Ptr{KRB5_PRINCNAME}
  cksum::Ptr{KRB5_CHECKSUM}
  cusec::Ptr{Int32}
  ctime::Ptr{Int32}
  subkey::Ptr{KRB5_ENCKEY}
  seqnum::Ptr{Int32}
  authorization::Ptr{KRB5_AUTHDATA}
end
@ctypedef KRB5_AUTHENTBODY krb5_authenticator_st
@ctypedef KRB5_AUTHENT STACK
type lhash_node_st
  data::Ptr{None}
  next::Ptr{Void}
  hash::Uint64
end
@ctypedef LHASH_NODE lhash_node_st
@ctypedef LHASH_COMP_FN_TYPE Ptr{Void}
@ctypedef LHASH_HASH_FN_TYPE Ptr{Void}
@ctypedef LHASH_DOALL_FN_TYPE Ptr{Void}
@ctypedef LHASH_DOALL_ARG_FN_TYPE Ptr{Void}
type lhash_st
  b::Ptr{Ptr{LHASH_NODE}}
  comp::LHASH_COMP_FN_TYPE
  hash::LHASH_HASH_FN_TYPE
  num_nodes::Uint32
  num_alloc_nodes::Uint32
  p::Uint32
  pmax::Uint32
  up_load::Uint64
  down_load::Uint64
  num_items::Uint64
  num_expands::Uint64
  num_expand_reallocs::Uint64
  num_contracts::Uint64
  num_contract_reallocs::Uint64
  num_hash_calls::Uint64
  num_comp_calls::Uint64
  num_insert::Uint64
  num_replace::Uint64
  num_delete::Uint64
  num_no_delete::Uint64
  num_retrieve::Uint64
  num_retrieve_miss::Uint64
  num_hash_comps::Uint64
  error::Int32
end
@ctypedef _LHASH lhash_st
type lhash_st_OPENSSL_STRING
  dummy::Int32
end
type lhash_st_OPENSSL_CSTRING
  dummy::Int32
end
type MD4state_st
  A::Uint32
  B::Uint32
  C::Uint32
  D::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef MD4_CTX MD4state_st
type MD5state_st
  A::Uint32
  B::Uint32
  C::Uint32
  D::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef MD5_CTX MD5state_st
type mdc2_ctx_st
  num::Uint32
  data::Void
  h::DES_cblock
  hh::DES_cblock
  pad_type::Int32
end
@ctypedef MDC2_CTX mdc2_ctx_st
@ctypedef block128_f Ptr{Void}
@ctypedef cbc128_f Ptr{Void}
@ctypedef ctr128_f Ptr{Void}
@ctypedef ccm128_f Ptr{Void}
@ctypedef GCM128_CONTEXT gcm128_context
@ctypedef CCM128_CONTEXT ccm128_context
@ctypedef XTS128_CONTEXT xts128_context
type obj_name_st
  _type::Int32
  alias::Int32
  name::Ptr{Uint8}
  data::Ptr{Uint8}
end
@ctypedef OBJ_NAME obj_name_st
type ocsp_cert_id_st
  hashAlgorithm::Ptr{X509_ALGOR}
  issuerNameHash::Ptr{ASN1_OCTET_STRING}
  issuerKeyHash::Ptr{ASN1_OCTET_STRING}
  serialNumber::Ptr{ASN1_INTEGER}
end
@ctypedef OCSP_CERTID ocsp_cert_id_st
type ocsp_one_request_st
  reqCert::Ptr{OCSP_CERTID}
  singleRequestExtensions::Ptr{STACK}
end
@ctypedef OCSP_ONEREQ ocsp_one_request_st
type ocsp_req_info_st
  version::Ptr{ASN1_INTEGER}
  requestorName::Ptr{GENERAL_NAME}
  requestList::Ptr{STACK}
  requestExtensions::Ptr{STACK}
end
@ctypedef OCSP_REQINFO ocsp_req_info_st
type ocsp_signature_st
  signatureAlgorithm::Ptr{X509_ALGOR}
  signature::Ptr{ASN1_BIT_STRING}
  certs::Ptr{STACK}
end
@ctypedef OCSP_SIGNATURE ocsp_signature_st
type ocsp_request_st
  tbsRequest::Ptr{OCSP_REQINFO}
  optionalSignature::Ptr{OCSP_SIGNATURE}
end
@ctypedef OCSP_REQUEST ocsp_request_st
type ocsp_resp_bytes_st
  responseType::Ptr{ASN1_OBJECT}
  response::Ptr{ASN1_OCTET_STRING}
end
@ctypedef OCSP_RESPBYTES ocsp_resp_bytes_st
type ocsp_response_st
  responseStatus::Ptr{ASN1_ENUMERATED}
  responseBytes::Ptr{OCSP_RESPBYTES}
end
type ocsp_responder_id_st
  _type::Int32
  value::
end
type ocsp_revoked_info_st
  revocationTime::Ptr{ASN1_GENERALIZEDTIME}
  revocationReason::Ptr{ASN1_ENUMERATED}
end
@ctypedef OCSP_REVOKEDINFO ocsp_revoked_info_st
type ocsp_cert_status_st
  _type::Int32
  value::
end
@ctypedef OCSP_CERTSTATUS ocsp_cert_status_st
type ocsp_single_response_st
  certId::Ptr{OCSP_CERTID}
  certStatus::Ptr{OCSP_CERTSTATUS}
  thisUpdate::Ptr{ASN1_GENERALIZEDTIME}
  nextUpdate::Ptr{ASN1_GENERALIZEDTIME}
  singleExtensions::Ptr{STACK}
end
@ctypedef OCSP_SINGLERESP ocsp_single_response_st
type ocsp_response_data_st
  version::Ptr{ASN1_INTEGER}
  responderId::Ptr{OCSP_RESPID}
  producedAt::Ptr{ASN1_GENERALIZEDTIME}
  responses::Ptr{STACK}
  responseExtensions::Ptr{STACK}
end
@ctypedef OCSP_RESPDATA ocsp_response_data_st
type ocsp_basic_response_st
  tbsResponseData::Ptr{OCSP_RESPDATA}
  signatureAlgorithm::Ptr{X509_ALGOR}
  signature::Ptr{ASN1_BIT_STRING}
  certs::Ptr{STACK}
end
@ctypedef OCSP_BASICRESP ocsp_basic_response_st
type ocsp_crl_id_st
  crlUrl::Ptr{ASN1_IA5STRING}
  crlNum::Ptr{ASN1_INTEGER}
  crlTime::Ptr{ASN1_GENERALIZEDTIME}
end
@ctypedef OCSP_CRLID ocsp_crl_id_st
type ocsp_service_locator_st
  issuer::Ptr{X509_NAME}
  locator::Ptr{STACK}
end
@ctypedef OCSP_SERVICELOC ocsp_service_locator_st
@ctypedef ASN1_INTEGER asn1_string_st
@ctypedef ASN1_ENUMERATED asn1_string_st
@ctypedef ASN1_BIT_STRING asn1_string_st
@ctypedef ASN1_OCTET_STRING asn1_string_st
@ctypedef ASN1_PRINTABLESTRING asn1_string_st
@ctypedef ASN1_T61STRING asn1_string_st
@ctypedef ASN1_IA5STRING asn1_string_st
@ctypedef ASN1_GENERALSTRING asn1_string_st
@ctypedef ASN1_UNIVERSALSTRING asn1_string_st
@ctypedef ASN1_BMPSTRING asn1_string_st
@ctypedef ASN1_UTCTIME asn1_string_st
@ctypedef ASN1_TIME asn1_string_st
@ctypedef ASN1_GENERALIZEDTIME asn1_string_st
@ctypedef ASN1_VISIBLESTRING asn1_string_st
@ctypedef ASN1_UTF8STRING asn1_string_st
@ctypedef ASN1_STRING asn1_string_st
@ctypedef ASN1_BOOLEAN Int32
@ctypedef ASN1_NULL Int32
@ctypedef ASN1_ITEM ASN1_ITEM_st
@ctypedef ASN1_PCTX asn1_pctx_st
@ctypedef BIGNUM bignum_st
@ctypedef BN_CTX bignum_ctx
@ctypedef BN_BLINDING bn_blinding_st
@ctypedef BN_MONT_CTX bn_mont_ctx_st
@ctypedef BN_RECP_CTX bn_recp_ctx_st
@ctypedef BN_GENCB bn_gencb_st
@ctypedef BUF_MEM buf_mem_st
@ctypedef EVP_CIPHER evp_cipher_st
@ctypedef EVP_CIPHER_CTX evp_cipher_ctx_st
@ctypedef EVP_MD env_md_st
@ctypedef EVP_MD_CTX env_md_ctx_st
@ctypedef EVP_PKEY evp_pkey_st
@ctypedef EVP_PKEY_ASN1_METHOD evp_pkey_asn1_method_st
@ctypedef EVP_PKEY_METHOD evp_pkey_method_st
@ctypedef EVP_PKEY_CTX evp_pkey_ctx_st
@ctypedef DH dh_st
@ctypedef DH_METHOD dh_method
@ctypedef DSA dsa_st
@ctypedef DSA_METHOD dsa_method
@ctypedef RSA rsa_st
@ctypedef RSA_METHOD rsa_meth_st
@ctypedef RAND_METHOD rand_meth_st
@ctypedef ECDH_METHOD ecdh_method
@ctypedef ECDSA_METHOD ecdsa_method
@ctypedef X509 x509_st
@ctypedef X509_ALGOR X509_algor_st
@ctypedef X509_CRL X509_crl_st
@ctypedef X509_CRL_METHOD x509_crl_method_st
@ctypedef X509_REVOKED x509_revoked_st
@ctypedef X509_NAME X509_name_st
@ctypedef X509_PUBKEY X509_pubkey_st
@ctypedef X509_STORE x509_store_st
@ctypedef X509_STORE_CTX x509_store_ctx_st
@ctypedef PKCS8_PRIV_KEY_INFO pkcs8_priv_key_info_st
@ctypedef X509V3_CTX v3_ext_ctx
@ctypedef CONF conf_st
@ctypedef STORE store_st
@ctypedef STORE_METHOD store_method_st
@ctypedef UI ui_st
@ctypedef UI_METHOD ui_method_st
@ctypedef ERR_FNS st_ERR_FNS
@ctypedef ENGINE engine_st
@ctypedef SSL ssl_st
@ctypedef SSL_CTX ssl_ctx_st
@ctypedef X509_POLICY_NODE X509_POLICY_NODE_st
@ctypedef X509_POLICY_LEVEL X509_POLICY_LEVEL_st
@ctypedef X509_POLICY_TREE X509_POLICY_TREE_st
@ctypedef X509_POLICY_CACHE X509_POLICY_CACHE_st
@ctypedef AUTHORITY_KEYID AUTHORITY_KEYID_st
@ctypedef DIST_POINT DIST_POINT_st
@ctypedef ISSUING_DIST_POINT ISSUING_DIST_POINT_st
@ctypedef NAME_CONSTRAINTS NAME_CONSTRAINTS_st
@ctypedef CRYPTO_EX_DATA crypto_ex_data_st
@ctypedef CRYPTO_EX_new Void
@ctypedef CRYPTO_EX_free Void
@ctypedef CRYPTO_EX_dup Void
@ctypedef OCSP_REQ_CTX ocsp_req_ctx_st
@ctypedef OCSP_RESPONSE ocsp_response_st
@ctypedef OCSP_RESPID ocsp_responder_id_st
type PEM_Encode_Seal_st
  encode::EVP_ENCODE_CTX
  md::EVP_MD_CTX
  cipher::EVP_CIPHER_CTX
end
@ctypedef PEM_ENCODE_SEAL_CTX PEM_Encode_Seal_st
type pem_recip_st
  name::Ptr{Uint8}
  dn::Ptr{X509_NAME}
  cipher::Int32
  key_enc::Int32
end
@ctypedef PEM_USER pem_recip_st
type pem_ctx_st
  _type::Int32
  proc_type::
  domain::Ptr{Uint8}
  DEK_info::
  originator::Ptr{PEM_USER}
  num_recipient::Int32
  recipient::Ptr{Ptr{PEM_USER}}
  md::Ptr{EVP_MD}
  md_enc::Int32
  md_len::Int32
  md_data::Ptr{Uint8}
  dec::Ptr{EVP_CIPHER}
  key_len::Int32
  key::Ptr{Uint8}
  data_enc::Int32
  data_len::Int32
  data::Ptr{Uint8}
end
@ctypedef PEM_CTX pem_ctx_st
@ctypedef pem_password_cb Void
type PKCS12_MAC_DATA
  dinfo::Ptr{X509_SIG}
  salt::Ptr{ASN1_OCTET_STRING}
  iter::Ptr{ASN1_INTEGER}
end
type PKCS12
  version::Ptr{ASN1_INTEGER}
  mac::Ptr{PKCS12_MAC_DATA}
  authsafes::Ptr{PKCS7}
end
type PKCS12_SAFEBAG
  _type::Ptr{ASN1_OBJECT}
  value::
  attrib::Ptr{STACK}
end
type pkcs12_bag_st
  _type::Ptr{ASN1_OBJECT}
  value::
end
@ctypedef PKCS12_BAGS pkcs12_bag_st
type pkcs7_issuer_and_serial_st
  issuer::Ptr{X509_NAME}
  serial::Ptr{ASN1_INTEGER}
end
@ctypedef PKCS7_ISSUER_AND_SERIAL pkcs7_issuer_and_serial_st
type pkcs7_signer_info_st
  version::Ptr{ASN1_INTEGER}
  issuer_and_serial::Ptr{PKCS7_ISSUER_AND_SERIAL}
  digest_alg::Ptr{X509_ALGOR}
  auth_attr::Ptr{STACK}
  digest_enc_alg::Ptr{X509_ALGOR}
  enc_digest::Ptr{ASN1_OCTET_STRING}
  unauth_attr::Ptr{STACK}
  pkey::Ptr{EVP_PKEY}
end
@ctypedef PKCS7_SIGNER_INFO pkcs7_signer_info_st
type pkcs7_recip_info_st
  version::Ptr{ASN1_INTEGER}
  issuer_and_serial::Ptr{PKCS7_ISSUER_AND_SERIAL}
  key_enc_algor::Ptr{X509_ALGOR}
  enc_key::Ptr{ASN1_OCTET_STRING}
  cert::Ptr{X509}
end
@ctypedef PKCS7_RECIP_INFO pkcs7_recip_info_st
type pkcs7_signed_st
  version::Ptr{ASN1_INTEGER}
  md_algs::Ptr{STACK}
  cert::Ptr{STACK}
  crl::Ptr{STACK}
  signer_info::Ptr{STACK}
  contents::Ptr{Void}
end
@ctypedef PKCS7_SIGNED pkcs7_signed_st
type pkcs7_enc_content_st
  content_type::Ptr{ASN1_OBJECT}
  algorithm::Ptr{X509_ALGOR}
  enc_data::Ptr{ASN1_OCTET_STRING}
  cipher::Ptr{EVP_CIPHER}
end
@ctypedef PKCS7_ENC_CONTENT pkcs7_enc_content_st
type pkcs7_enveloped_st
  version::Ptr{ASN1_INTEGER}
  recipientinfo::Ptr{STACK}
  enc_data::Ptr{PKCS7_ENC_CONTENT}
end
@ctypedef PKCS7_ENVELOPE pkcs7_enveloped_st
type pkcs7_signedandenveloped_st
  version::Ptr{ASN1_INTEGER}
  md_algs::Ptr{STACK}
  cert::Ptr{STACK}
  crl::Ptr{STACK}
  signer_info::Ptr{STACK}
  enc_data::Ptr{PKCS7_ENC_CONTENT}
  recipientinfo::Ptr{STACK}
end
@ctypedef PKCS7_SIGN_ENVELOPE pkcs7_signedandenveloped_st
type pkcs7_digest_st
  version::Ptr{ASN1_INTEGER}
  md::Ptr{X509_ALGOR}
  contents::Ptr{Void}
  digest::Ptr{ASN1_OCTET_STRING}
end
@ctypedef PKCS7_DIGEST pkcs7_digest_st
type pkcs7_encrypted_st
  version::Ptr{ASN1_INTEGER}
  enc_data::Ptr{PKCS7_ENC_CONTENT}
end
@ctypedef PKCS7_ENCRYPT pkcs7_encrypted_st
type pkcs7_st
  asn1::Ptr{Uint8}
  length::Int64
  state::Int32
  detached::Int32
  _type::Ptr{ASN1_OBJECT}
  d::
end
@ctypedef PKCS7 pkcs7_st
@ctypedef pqueue Ptr{Void}
type _pitem
  priority::Void
  data::Ptr{None}
  next::Ptr{Void}
end
@ctypedef pitem _pitem
@ctypedef piterator Ptr{Void}
type rc2_key_st
  data::Void
end
@ctypedef RC2_KEY rc2_key_st
type rc4_key_st
  x::Uint8
  y::Uint8
  data::Void
end
@ctypedef RC4_KEY rc4_key_st
type RIPEMD160state_st
  A::Uint32
  B::Uint32
  C::Uint32
  D::Uint32
  E::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef RIPEMD160_CTX RIPEMD160state_st
type rsa_pss_params_st
  hashAlgorithm::Ptr{X509_ALGOR}
  maskGenAlgorithm::Ptr{X509_ALGOR}
  saltLength::Ptr{ASN1_INTEGER}
  trailerField::Ptr{ASN1_INTEGER}
end
@ctypedef RSA_PSS_PARAMS rsa_pss_params_st
@ctypedef OPENSSL_STRING Ptr{Uint8}
@ctypedef OPENSSL_CSTRING Ptr{Uint8}
type stack_st_OPENSSL_STRING
  stack::Int32
end
@ctypedef OPENSSL_BLOCK Ptr{None}
type stack_st_OPENSSL_BLOCK
  stack::Int32
end
type seed_key_st
  data::Void
end
@ctypedef SEED_KEY_SCHEDULE seed_key_st
type SHAstate_st
  h0::Uint32
  h1::Uint32
  h2::Uint32
  h3::Uint32
  h4::Uint32
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
end
@ctypedef SHA_CTX SHAstate_st
type SHA256state_st
  h::Void
  Nl::Uint32
  Nh::Uint32
  data::Void
  num::Uint32
  md_len::Uint32
end
@ctypedef SHA256_CTX SHA256state_st
type SHA512state_st
  h::Void
  Nl::Uint64
  Nh::Uint64
  u::
  num::Uint32
  md_len::Uint32
end
@ctypedef SHA512_CTX SHA512state_st
type SRP_gN_cache_st
  b64_bn::Ptr{Uint8}
  bn::Ptr{BIGNUM}
end
@ctypedef SRP_gN_cache SRP_gN_cache_st
type SRP_user_pwd_st
  id::Ptr{Uint8}
  s::Ptr{BIGNUM}
  v::Ptr{BIGNUM}
  g::Ptr{BIGNUM}
  N::Ptr{BIGNUM}
  info::Ptr{Uint8}
end
@ctypedef SRP_user_pwd SRP_user_pwd_st
type SRP_VBASE_st
  users_pwd::Ptr{STACK}
  gN_cache::Ptr{STACK}
  seed_key::Ptr{Uint8}
  default_g::Ptr{BIGNUM}
  default_N::Ptr{BIGNUM}
end
@ctypedef SRP_VBASE SRP_VBASE_st
type SRP_gN_st
  id::Ptr{Uint8}
  g::Ptr{BIGNUM}
  N::Ptr{BIGNUM}
end
@ctypedef SRP_gN SRP_gN_st
@ctypedef ssl_crock_st Ptr{Void}
@ctypedef TLS_SESSION_TICKET_EXT tls_session_ticket_ext_st
@ctypedef SSL_METHOD ssl_method_st
@ctypedef SSL_CIPHER ssl_cipher_st
@ctypedef SSL_SESSION ssl_session_st
type srtp_protection_profile_st
  name::Ptr{Uint8}
  id::Uint64
end
@ctypedef SRTP_PROTECTION_PROFILE srtp_protection_profile_st
@ctypedef tls_session_ticket_ext_cb_fn Ptr{Void}
@ctypedef tls_session_secret_cb_fn Ptr{Void}
type srp_ctx_st
  SRP_cb_arg::Ptr{None}
  TLS_ext_srp_username_callback::Ptr{Void}
  SRP_verify_param_callback::Ptr{Void}
  SRP_give_srp_client_pwd_callback::Ptr{Void}
  login::Ptr{Uint8}
  N::Ptr{BIGNUM}
  g::Ptr{BIGNUM}
  s::Ptr{BIGNUM}
  B::Ptr{BIGNUM}
  A::Ptr{BIGNUM}
  a::Ptr{BIGNUM}
  b::Ptr{BIGNUM}
  v::Ptr{BIGNUM}
  info::Ptr{Uint8}
  strength::Int32
  srp_Mask::Uint64
end
@ctypedef SRP_CTX srp_ctx_st
@ctypedef GEN_SESSION_CB Ptr{Void}
@ctypedef SSL_COMP ssl_comp_st
type ssl2_state_st
  three_byte_header::Int32
  clear_text::Int32
  escape::Int32
  ssl2_rollback::Int32
  wnum::Uint32
  wpend_tot::Int32
  wpend_buf::Ptr{Uint8}
  wpend_off::Int32
  wpend_len::Int32
  wpend_ret::Int32
  rbuf_left::Int32
  rbuf_offs::Int32
  rbuf::Ptr{Uint8}
  wbuf::Ptr{Uint8}
  write_ptr::Ptr{Uint8}
  padding::Uint32
  rlength::Uint32
  ract_data_length::Int32
  wlength::Uint32
  wact_data_length::Int32
  ract_data::Ptr{Uint8}
  wact_data::Ptr{Uint8}
  mac_data::Ptr{Uint8}
  read_key::Ptr{Uint8}
  write_key::Ptr{Uint8}
  challenge_length::Uint32
  challenge::Void
  conn_id_length::Uint32
  conn_id::Void
  key_material_length::Uint32
  key_material::Void
  read_sequence::Uint64
  write_sequence::Uint64
  tmp::
end
@ctypedef SSL2_STATE ssl2_state_st
type ssl3_record_st
  _type::Int32
  length::Uint32
  off::Uint32
  data::Ptr{Uint8}
  input::Ptr{Uint8}
  comp::Ptr{Uint8}
  epoch::Uint64
  seq_num::Void
end
@ctypedef SSL3_RECORD ssl3_record_st
type ssl3_buffer_st
  buf::Ptr{Uint8}
  len::Csize_t
  offset::Int32
  left::Int32
end
@ctypedef SSL3_BUFFER ssl3_buffer_st
type ssl3_state_st
  flags::Int64
  delay_buf_pop_ret::Int32
  read_sequence::Void
  read_mac_secret_size::Int32
  read_mac_secret::Void
  write_sequence::Void
  write_mac_secret_size::Int32
  write_mac_secret::Void
  server_random::Void
  client_random::Void
  need_empty_fragments::Int32
  empty_fragment_done::Int32
  init_extra::Int32
  rbuf::SSL3_BUFFER
  wbuf::SSL3_BUFFER
  rrec::SSL3_RECORD
  wrec::SSL3_RECORD
  alert_fragment::Void
  alert_fragment_len::Uint32
  handshake_fragment::Void
  handshake_fragment_len::Uint32
  wnum::Uint32
  wpend_tot::Int32
  wpend_type::Int32
  wpend_ret::Int32
  wpend_buf::Ptr{Uint8}
  handshake_buffer::Ptr{BIO}
  handshake_dgst::Ptr{Ptr{EVP_MD_CTX}}
  change_cipher_spec::Int32
  warn_alert::Int32
  fatal_alert::Int32
  alert_dispatch::Int32
  send_alert::Void
  renegotiate::Int32
  total_renegotiations::Int32
  num_renegotiations::Int32
  in_read_app_data::Int32
  client_opaque_prf_input::Ptr{None}
  client_opaque_prf_input_len::Csize_t
  server_opaque_prf_input::Ptr{None}
  server_opaque_prf_input_len::Csize_t
  tmp::
  previous_client_finished::Void
  previous_client_finished_len::Uint8
  previous_server_finished::Void
  previous_server_finished_len::Uint8
  send_connection_binding::Int32
  next_proto_neg_seen::Int32
end
@ctypedef SSL3_STATE ssl3_state_st
type stack_st
  num::Int32
  data::Ptr{Ptr{Uint8}}
  sorted::Int32
  num_alloc::Int32
  comp::Ptr{Void}
end
@ctypedef _STACK stack_st
type TS_msg_imprint_st
  hash_algo::Ptr{X509_ALGOR}
  hashed_msg::Ptr{ASN1_OCTET_STRING}
end
@ctypedef TS_MSG_IMPRINT TS_msg_imprint_st
type TS_req_st
  version::Ptr{ASN1_INTEGER}
  msg_imprint::Ptr{TS_MSG_IMPRINT}
  policy_id::Ptr{ASN1_OBJECT}
  nonce::Ptr{ASN1_INTEGER}
  cert_req::ASN1_BOOLEAN
  extensions::Ptr{STACK}
end
@ctypedef TS_REQ TS_req_st
type TS_accuracy_st
  seconds::Ptr{ASN1_INTEGER}
  millis::Ptr{ASN1_INTEGER}
  micros::Ptr{ASN1_INTEGER}
end
@ctypedef TS_ACCURACY TS_accuracy_st
type TS_tst_info_st
  version::Ptr{ASN1_INTEGER}
  policy_id::Ptr{ASN1_OBJECT}
  msg_imprint::Ptr{TS_MSG_IMPRINT}
  serial::Ptr{ASN1_INTEGER}
  time::Ptr{ASN1_GENERALIZEDTIME}
  accuracy::Ptr{TS_ACCURACY}
  ordering::ASN1_BOOLEAN
  nonce::Ptr{ASN1_INTEGER}
  tsa::Ptr{GENERAL_NAME}
  extensions::Ptr{STACK}
end
@ctypedef TS_TST_INFO TS_tst_info_st
type TS_status_info_st
  status::Ptr{ASN1_INTEGER}
  text::Ptr{STACK}
  failure_info::Ptr{ASN1_BIT_STRING}
end
@ctypedef TS_STATUS_INFO TS_status_info_st
type TS_resp_st
  status_info::Ptr{TS_STATUS_INFO}
  token::Ptr{PKCS7}
  tst_info::Ptr{TS_TST_INFO}
end
@ctypedef TS_RESP TS_resp_st
type ESS_issuer_serial
  issuer::Ptr{STACK}
  serial::Ptr{ASN1_INTEGER}
end
@ctypedef ESS_ISSUER_SERIAL ESS_issuer_serial
type ESS_cert_id
  hash::Ptr{ASN1_OCTET_STRING}
  issuer_serial::Ptr{ESS_ISSUER_SERIAL}
end
@ctypedef ESS_CERT_ID ESS_cert_id
type ESS_signing_cert
  cert_ids::Ptr{STACK}
  policy_info::Ptr{STACK}
end
@ctypedef ESS_SIGNING_CERT ESS_signing_cert
@ctypedef TS_serial_cb Ptr{Void}
@ctypedef TS_time_cb Ptr{Void}
@ctypedef TS_extension_cb Ptr{Void}
@ctypedef TS_RESP_CTX TS_resp_ctx
type TS_verify_ctx
  flags::Uint32
  store::Ptr{X509_STORE}
  certs::Ptr{STACK}
  policy::Ptr{ASN1_OBJECT}
  md_alg::Ptr{X509_ALGOR}
  imprint::Ptr{Uint8}
  imprint_len::Uint32
  data::Ptr{BIO}
  nonce::Ptr{ASN1_INTEGER}
  tsa_name::Ptr{GENERAL_NAME}
end
@ctypedef TS_VERIFY_CTX TS_verify_ctx
@ctypedef OPENSSL_PSTRING Ptr{Int32}
type txt_db_st
  num_fields::Int32
  data::Ptr{STACK}
  LHASH_OF::Void
  qual::Ptr{Ptr{Void}}
  error::Int64
  arg1::Int64
  arg2::Int64
  arg_row::Ptr{Int32}
end
@ctypedef TXT_DB txt_db_st
@ctypedef UI_STRING ui_string_st
# enum UI_string_types
const UIT_NONE = 0
const UIT_PROMPT = 1
const UIT_VERIFY = 2
const UIT_BOOLEAN = 3
const UIT_INFO = 4
const UIT_ERROR = 5
# end
type WHIRLPOOL_CTX
  H::
  data::Void
  bitoff::Uint32
  bitlen::Void
end
type X509_objects_st
  nid::Int32
  a2i::Ptr{Void}
  i2a::Ptr{Void}
end
@ctypedef X509_OBJECTS X509_objects_st
@ctypedef X509_ALGORS STACK
type X509_val_st
  notBefore::Ptr{ASN1_TIME}
  notAfter::Ptr{ASN1_TIME}
end
@ctypedef X509_VAL X509_val_st
type X509_sig_st
  algor::Ptr{X509_ALGOR}
  digest::Ptr{ASN1_OCTET_STRING}
end
@ctypedef X509_SIG X509_sig_st
type X509_name_entry_st
  object::Ptr{ASN1_OBJECT}
  value::Ptr{ASN1_STRING}
  set::Int32
  size::Int32
end
@ctypedef X509_NAME_ENTRY X509_name_entry_st
type X509_extension_st
  object::Ptr{ASN1_OBJECT}
  critical::ASN1_BOOLEAN
  value::Ptr{ASN1_OCTET_STRING}
end
@ctypedef X509_EXTENSION X509_extension_st
@ctypedef X509_EXTENSIONS STACK
type x509_attributes_st
  object::Ptr{ASN1_OBJECT}
  single::Int32
  value::
end
@ctypedef X509_ATTRIBUTE x509_attributes_st
type X509_req_info_st
  enc::ASN1_ENCODING
  version::Ptr{ASN1_INTEGER}
  subject::Ptr{X509_NAME}
  pubkey::Ptr{Int32}
  attributes::Ptr{STACK}
end
@ctypedef X509_REQ_INFO X509_req_info_st
type X509_req_st
  req_info::Ptr{X509_REQ_INFO}
  sig_alg::Ptr{X509_ALGOR}
  signature::Ptr{ASN1_BIT_STRING}
  references::Int32
end
@ctypedef X509_REQ X509_req_st
type x509_cinf_st
  version::Ptr{ASN1_INTEGER}
  serialNumber::Ptr{ASN1_INTEGER}
  signature::Ptr{X509_ALGOR}
  issuer::Ptr{X509_NAME}
  validity::Ptr{X509_VAL}
  subject::Ptr{X509_NAME}
  key::Ptr{Int32}
  issuerUID::Ptr{ASN1_BIT_STRING}
  subjectUID::Ptr{ASN1_BIT_STRING}
  extensions::Ptr{STACK}
  enc::ASN1_ENCODING
end
@ctypedef X509_CINF x509_cinf_st
type x509_cert_aux_st
  trust::Ptr{STACK}
  reject::Ptr{STACK}
  alias::Ptr{ASN1_UTF8STRING}
  keyid::Ptr{ASN1_OCTET_STRING}
  other::Ptr{STACK}
end
@ctypedef X509_CERT_AUX x509_cert_aux_st
type x509_trust_st
  trust::Int32
  flags::Int32
  check_trust::Ptr{Void}
  name::Ptr{Uint8}
  arg1::Int32
  arg2::Ptr{None}
end
@ctypedef X509_TRUST x509_trust_st
type x509_cert_pair_st
  forward::Ptr{X509}
  reverse::Ptr{X509}
end
@ctypedef X509_CERT_PAIR x509_cert_pair_st
type X509_crl_info_st
  version::Ptr{ASN1_INTEGER}
  sig_alg::Ptr{X509_ALGOR}
  issuer::Ptr{X509_NAME}
  lastUpdate::Ptr{ASN1_TIME}
  nextUpdate::Ptr{ASN1_TIME}
  revoked::Ptr{STACK}
  extensions::Ptr{STACK}
  enc::ASN1_ENCODING
end
@ctypedef X509_CRL_INFO X509_crl_info_st
type private_key_st
  version::Int32
  enc_algor::Ptr{X509_ALGOR}
  enc_pkey::Ptr{ASN1_OCTET_STRING}
  dec_pkey::Ptr{EVP_PKEY}
  key_length::Int32
  key_data::Ptr{Uint8}
  key_free::Int32
  cipher::EVP_CIPHER_INFO
  references::Int32
end
@ctypedef X509_PKEY private_key_st
type X509_info_st
  x509::Ptr{X509}
  crl::Ptr{X509_CRL}
  x_pkey::Ptr{X509_PKEY}
  enc_cipher::EVP_CIPHER_INFO
  enc_len::Int32
  enc_data::Ptr{Uint8}
  references::Int32
end
@ctypedef X509_INFO X509_info_st
type Netscape_spkac_st
  pubkey::Ptr{Int32}
  challenge::Ptr{ASN1_IA5STRING}
end
@ctypedef NETSCAPE_SPKAC Netscape_spkac_st
type Netscape_spki_st
  spkac::Ptr{NETSCAPE_SPKAC}
  sig_algor::Ptr{X509_ALGOR}
  signature::Ptr{ASN1_BIT_STRING}
end
@ctypedef NETSCAPE_SPKI Netscape_spki_st
type Netscape_certificate_sequence
  _type::Ptr{ASN1_OBJECT}
  certs::Ptr{STACK}
end
@ctypedef NETSCAPE_CERT_SEQUENCE Netscape_certificate_sequence
type PBEPARAM_st
  salt::Ptr{ASN1_OCTET_STRING}
  iter::Ptr{ASN1_INTEGER}
end
@ctypedef PBEPARAM PBEPARAM_st
type PBE2PARAM_st
  keyfunc::Ptr{X509_ALGOR}
  encryption::Ptr{X509_ALGOR}
end
@ctypedef PBE2PARAM PBE2PARAM_st
type PBKDF2PARAM_st
  salt::Ptr{ASN1_TYPE}
  iter::Ptr{ASN1_INTEGER}
  keylength::Ptr{ASN1_INTEGER}
  prf::Ptr{X509_ALGOR}
end
@ctypedef PBKDF2PARAM PBKDF2PARAM_st
@ctypedef X509V3_EXT_NEW Ptr{Void}
@ctypedef X509V3_EXT_FREE Ptr{Void}
@ctypedef X509V3_EXT_D2I Ptr{Void}
@ctypedef X509V3_EXT_I2D Ptr{Void}
@ctypedef X509V3_EXT_I2V Ptr{Void}
@ctypedef X509V3_EXT_V2I Ptr{Void}
@ctypedef X509V3_EXT_I2S Ptr{Void}
@ctypedef X509V3_EXT_S2I Ptr{Void}
@ctypedef X509V3_EXT_I2R Ptr{Void}
@ctypedef X509V3_EXT_R2I Ptr{Void}
type X509V3_CONF_METHOD_st
  get_string::Ptr{Void}
  get_section::Ptr{Void}
  free_string::Ptr{Void}
  free_section::Ptr{Void}
end
@ctypedef X509V3_CONF_METHOD X509V3_CONF_METHOD_st
@ctypedef X509V3_EXT_METHOD v3_ext_method
@ctypedef ENUMERATED_NAMES BIT_STRING_BITNAME
type BASIC_CONSTRAINTS_st
  ca::Int32
  pathlen::Ptr{ASN1_INTEGER}
end
@ctypedef BASIC_CONSTRAINTS BASIC_CONSTRAINTS_st
type PKEY_USAGE_PERIOD_st
  notBefore::Ptr{ASN1_GENERALIZEDTIME}
  notAfter::Ptr{ASN1_GENERALIZEDTIME}
end
@ctypedef PKEY_USAGE_PERIOD PKEY_USAGE_PERIOD_st
type otherName_st
  type_id::Ptr{ASN1_OBJECT}
  value::Ptr{ASN1_TYPE}
end
@ctypedef OTHERNAME otherName_st
type EDIPartyName_st
  nameAssigner::Ptr{ASN1_STRING}
  partyName::Ptr{ASN1_STRING}
end
@ctypedef EDIPARTYNAME EDIPartyName_st
type GENERAL_NAME_st
  _type::Int32
  d::
end
@ctypedef GENERAL_NAME GENERAL_NAME_st
@ctypedef GENERAL_NAMES STACK
type ACCESS_DESCRIPTION_st
  method::Ptr{ASN1_OBJECT}
  location::Ptr{GENERAL_NAME}
end
@ctypedef ACCESS_DESCRIPTION ACCESS_DESCRIPTION_st
@ctypedef AUTHORITY_INFO_ACCESS STACK
@ctypedef EXTENDED_KEY_USAGE STACK
type DIST_POINT_NAME_st
  _type::Int32
  name::
  dpname::Ptr{X509_NAME}
end
@ctypedef DIST_POINT_NAME DIST_POINT_NAME_st
@ctypedef CRL_DIST_POINTS STACK
type SXNET_ID_st
  zone::Ptr{ASN1_INTEGER}
  user::Ptr{ASN1_OCTET_STRING}
end
@ctypedef SXNETID SXNET_ID_st
type SXNET_st
  version::Ptr{ASN1_INTEGER}
  ids::Ptr{STACK}
end
@ctypedef SXNET SXNET_st
type NOTICEREF_st
  organization::Ptr{ASN1_STRING}
  noticenos::Ptr{STACK}
end
@ctypedef NOTICEREF NOTICEREF_st
type USERNOTICE_st
  noticeref::Ptr{NOTICEREF}
  exptext::Ptr{ASN1_STRING}
end
@ctypedef USERNOTICE USERNOTICE_st
type POLICYQUALINFO_st
  pqualid::Ptr{ASN1_OBJECT}
  d::
end
@ctypedef POLICYQUALINFO POLICYQUALINFO_st
type POLICYINFO_st
  policyid::Ptr{ASN1_OBJECT}
  qualifiers::Ptr{STACK}
end
@ctypedef POLICYINFO POLICYINFO_st
@ctypedef CERTIFICATEPOLICIES STACK
type POLICY_MAPPING_st
  issuerDomainPolicy::Ptr{ASN1_OBJECT}
  subjectDomainPolicy::Ptr{ASN1_OBJECT}
end
@ctypedef POLICY_MAPPING POLICY_MAPPING_st
@ctypedef POLICY_MAPPINGS STACK
type GENERAL_SUBTREE_st
  base::Ptr{GENERAL_NAME}
  minimum::Ptr{ASN1_INTEGER}
  maximum::Ptr{ASN1_INTEGER}
end
@ctypedef GENERAL_SUBTREE GENERAL_SUBTREE_st
type POLICY_CONSTRAINTS_st
  requireExplicitPolicy::Ptr{ASN1_INTEGER}
  inhibitPolicyMapping::Ptr{ASN1_INTEGER}
end
@ctypedef POLICY_CONSTRAINTS POLICY_CONSTRAINTS_st
type PROXY_POLICY_st
  policyLanguage::Ptr{ASN1_OBJECT}
  policy::Ptr{ASN1_OCTET_STRING}
end
@ctypedef PROXY_POLICY PROXY_POLICY_st
type PROXY_CERT_INFO_EXTENSION_st
  pcPathLengthConstraint::Ptr{ASN1_INTEGER}
  proxyPolicy::Ptr{PROXY_POLICY}
end
@ctypedef PROXY_CERT_INFO_EXTENSION PROXY_CERT_INFO_EXTENSION_st
type x509_purpose_st
  purpose::Int32
  trust::Int32
  flags::Int32
  check_purpose::Ptr{Void}
  name::Ptr{Uint8}
  sname::Ptr{Uint8}
  usr_data::Ptr{None}
end
@ctypedef X509_PURPOSE x509_purpose_st
