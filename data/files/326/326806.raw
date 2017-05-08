#!/usr/bin/env julia

abstract Entry

using YAML

type SidebarEntry <: Entry
    lines::Array{String}
    heading::String
end

type MainEntry <: Entry
    lines::Array{String}
    heading::String
    time::String
    qualifier::String
end

type ContactEntry <: Entry
    lines::Array{String}
    address::Array{String}
    email::String
    websites::Array{String}
end

## Constructors

SidebarEntry(sidebar_info::Dict) =
    try
        SidebarEntry(
                     sidebar_info["desc"],
                     sidebar_info["heading"],
                     )
    catch ee
        print_fielderror_info(ee, sidebar_info)
    end

MainEntry(main_info::Dict) =
    try
        MainEntry(
                  main_info["desc"],
                  main_info["heading"],
                  string(main_info["time"]),
                  main_info["qualifier"],
                  )
    catch ee
        print_fielderror_info(ee, main_info)
    end

ContactEntry(contact_info::Dict) =
    try
        ContactEntry(
                     get(contact_info, "line", [""]),
                     contact_info["address"],
                     contact_info["email"],
                     contact_info["website"],
                     )
    catch ee
        print_fielderror_info(ee, contact_info)
    end

function print_fielderror_info(ee::Exception, info::Dict)
    if typeof(ee) == KeyError
        info_keys = collect(keys(info))
        error_text = join(String["$(info_key): $(info[info_key])" for info_key in info_keys], "\n")
        println("Required field '$(ee.key)' not found in this entry: $(error_text)")
        exit(1)
    else
        throw(ee)
    end
end

function generate_resume(in_path::String, out_path::String, template_path::String)
    dict = YAML.load_file(in_path)
    sidebar_entries = SidebarEntry[SidebarEntry(sidebar_dict) for sidebar_dict in dict["sidebar"]]
    contact = ContactEntry(dict["contact"])
    main_entries = dict["main"]
        ## MainEntry[MainEntry(main_dict) for main_dict in dict["main"]]
    latex_output = generate_latex(template_path, dict, sidebar_entries, contact, main_entries)
    println(latex_output)
    f = open(out_path, "w")
    println(f, latex_output)
    close(f)
end

function generate_latex(template_path::String, dict::Dict, sidebar_entries::Array{SidebarEntry}, contact::ContactEntry, main_entries::Dict)
    result = readall(open(template_path))
    result = replace_tag(result, "name", dict["name"])
    result = replace_tag(result, "contact", generate_latex(contact))
    result = replace_tag(result, "sidebar", generate_latex(sidebar_entries))
    result = replace_tag(result, "main", generate_latex(main_entries))
    return result
end

function generate_latex(contact::ContactEntry)
    contact_text = readall(open("tex/contact.tex"))
    contact_text = replace_tag(contact_text, "address", contact.address)
    contact_text = replace_tag(contact_text, "email", contact.email)
    contact_text = replace_tag(contact_text, "website", contact.websites)
    return contact_text
end

function generate_latex(entries::Array{Entry})
    return join([generate_latex(entry) for entry in entries], "\n\n")
end

function generate_latex(entries::Array{SidebarEntry})
    return join([generate_latex(entry) for entry in entries], "\n\n")
end

function generate_latex(main_dict::Dict)
    sep = "\n\n"
    main_text = readall(open("tex/main.tex"))
    headings = String[key for key in collect(keys(main_dict))]
    main_entries = [replace_tag(main_text, "heading", heading) for heading in headings]
    for ii in 1:length(main_entries)
        main_entries[ii] = replace_tag(main_entries[ii],
                                       "body",
                                       join(String[
                                                   generate_latex(MainEntry(main_entry)) for main_entry in main_dict[headings[ii]]
                                                   ],
                                            "\n\n"),
                                       )
    end
    return join(main_entries, sep)
end

function generate_latex(entry::SidebarEntry)
    sep = """\\\\
      ~\\\\\n"""
    entry_text = readall(open("tex/sidebar.tex"))
    entry_text = replace_tag(entry_text, "heading", entry.heading)
    entry_text = replace_tag(entry_text, "lines", join(entry.lines, sep))
    return entry_text
end

function generate_latex(entry::MainEntry)
    entry_text = readall(open("tex/main_entry.tex"))
    entry_text = replace_tag(entry_text, "heading", entry.heading)
    entry_text = replace_tag(entry_text, "qualifier", entry.qualifier)
    entry_text = replace_tag(entry_text, "time", entry.time)
    entry_text = replace_tag(entry_text, "lines", join(entry.lines, "\n\n"))
    return entry_text
end

function replace_tag(body::String, tag_name::String, replacement::String)
    return replace(body, "[;$tag_name;]", replacement)
end

function replace_tag(body::String, tag_name::String, replacement_array::Array{String})
    replacement = join([line for line in replacement_array], "\n\n")
    replace_tag(body, tag_name, replacement)
end

function get_entry_lines(entry_dict::Dict, prefix::String)
    lines = filter(key->beginswith(key, prefix),
                   sort(collect(keys(entry_dict))))
    return String[string(entry_dict[line]) for line in lines]
end




    
