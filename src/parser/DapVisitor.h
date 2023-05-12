
// Generated from Dap.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "DapParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by DapParser.
 */
class  DapVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by DapParser.
   */
    virtual std::any visitParse(DapParser::ParseContext *context) = 0;

    virtual std::any visitSas_stmt_list(DapParser::Sas_stmt_listContext *context) = 0;

    virtual std::any visitIf_stmt(DapParser::If_stmtContext *context) = 0;

    virtual std::any visitIf_then_else_stmt(DapParser::If_then_else_stmtContext *context) = 0;

    virtual std::any visitDelete_stmt(DapParser::Delete_stmtContext *context) = 0;

    virtual std::any visitExpression(DapParser::ExpressionContext *context) = 0;

    virtual std::any visitExpressionList(DapParser::ExpressionListContext *context) = 0;

    virtual std::any visitOf_var_list(DapParser::Of_var_listContext *context) = 0;

    virtual std::any visitIdentifiers_list(DapParser::Identifiers_listContext *context) = 0;

    virtual std::any visitIn_var_list(DapParser::In_var_listContext *context) = 0;

    virtual std::any visitColonInts(DapParser::ColonIntsContext *context) = 0;

    virtual std::any visitLiteral(DapParser::LiteralContext *context) = 0;

    virtual std::any visitVariables(DapParser::VariablesContext *context) = 0;

    virtual std::any visitAbort_main(DapParser::Abort_mainContext *context) = 0;

    virtual std::any visitAbort_stmt(DapParser::Abort_stmtContext *context) = 0;

    virtual std::any visitFile_spec(DapParser::File_specContext *context) = 0;

    virtual std::any visitProc_main(DapParser::Proc_mainContext *context) = 0;

    virtual std::any visitProc_stmt(DapParser::Proc_stmtContext *context) = 0;

    virtual std::any visitProc_name(DapParser::Proc_nameContext *context) = 0;

    virtual std::any visitArray_main(DapParser::Array_mainContext *context) = 0;

    virtual std::any visitArray_stmt(DapParser::Array_stmtContext *context) = 0;

    virtual std::any visitArray_name(DapParser::Array_nameContext *context) = 0;

    virtual std::any visitArray_subscript(DapParser::Array_subscriptContext *context) = 0;

    virtual std::any visitArray_elements(DapParser::Array_elementsContext *context) = 0;

    virtual std::any visitInitial_value_list(DapParser::Initial_value_listContext *context) = 0;

    virtual std::any visitInitial_value_list_item(DapParser::Initial_value_list_itemContext *context) = 0;

    virtual std::any visitInitial_value_list_bk(DapParser::Initial_value_list_bkContext *context) = 0;

    virtual std::any visitConstant_iter_value(DapParser::Constant_iter_valueContext *context) = 0;

    virtual std::any visitConstant_value(DapParser::Constant_valueContext *context) = 0;

    virtual std::any visitAssign_main(DapParser::Assign_mainContext *context) = 0;

    virtual std::any visitAssign_stmt(DapParser::Assign_stmtContext *context) = 0;

    virtual std::any visitBy_main(DapParser::By_mainContext *context) = 0;

    virtual std::any visitBy_stmt(DapParser::By_stmtContext *context) = 0;

    virtual std::any visitCall_main(DapParser::Call_mainContext *context) = 0;

    virtual std::any visitCall_stmt(DapParser::Call_stmtContext *context) = 0;

    virtual std::any visitData_main(DapParser::Data_mainContext *context) = 0;

    virtual std::any visitData_stmt(DapParser::Data_stmtContext *context) = 0;

    virtual std::any visitDataset_name_opt(DapParser::Dataset_name_optContext *context) = 0;

    virtual std::any visitDatastmt_cmd(DapParser::Datastmt_cmdContext *context) = 0;

    virtual std::any visitView_dsname_opt(DapParser::View_dsname_optContext *context) = 0;

    virtual std::any visitView_name(DapParser::View_nameContext *context) = 0;

    virtual std::any visitDataset_name(DapParser::Dataset_nameContext *context) = 0;

    virtual std::any visitProgram_name(DapParser::Program_nameContext *context) = 0;

    virtual std::any visitPasswd_opt(DapParser::Passwd_optContext *context) = 0;

    virtual std::any visitSource_opt(DapParser::Source_optContext *context) = 0;

    virtual std::any visitDatalines_main(DapParser::Datalines_mainContext *context) = 0;

    virtual std::any visitDatalines_stmt(DapParser::Datalines_stmtContext *context) = 0;

    virtual std::any visitDatalines4_stmt(DapParser::Datalines4_stmtContext *context) = 0;

    virtual std::any visitDrop_main(DapParser::Drop_mainContext *context) = 0;

    virtual std::any visitDrop_stmt(DapParser::Drop_stmtContext *context) = 0;

    virtual std::any visitInfile_main(DapParser::Infile_mainContext *context) = 0;

    virtual std::any visitInfile_stmt(DapParser::Infile_stmtContext *context) = 0;

    virtual std::any visitFile_specification(DapParser::File_specificationContext *context) = 0;

    virtual std::any visitDevice_type(DapParser::Device_typeContext *context) = 0;

    virtual std::any visitInfile_options(DapParser::Infile_optionsContext *context) = 0;

    virtual std::any visitInput_main(DapParser::Input_mainContext *context) = 0;

    virtual std::any visitInput_stmt(DapParser::Input_stmtContext *context) = 0;

    virtual std::any visitPut_stmt(DapParser::Put_stmtContext *context) = 0;

    virtual std::any visitInput_specification(DapParser::Input_specificationContext *context) = 0;

    virtual std::any visitPut_specification(DapParser::Put_specificationContext *context) = 0;

    virtual std::any visitPointer_control(DapParser::Pointer_controlContext *context) = 0;

    virtual std::any visitInformat_list(DapParser::Informat_listContext *context) = 0;

    virtual std::any visitInput_variable_format(DapParser::Input_variable_formatContext *context) = 0;

    virtual std::any visitInput_variable(DapParser::Input_variableContext *context) = 0;

    virtual std::any visitPut_variable_format(DapParser::Put_variable_formatContext *context) = 0;

    virtual std::any visitPut_variable(DapParser::Put_variableContext *context) = 0;

    virtual std::any visitColumn_point_control(DapParser::Column_point_controlContext *context) = 0;

    virtual std::any visitLine_point_control(DapParser::Line_point_controlContext *context) = 0;

    virtual std::any visitFormat_modifier(DapParser::Format_modifierContext *context) = 0;

    virtual std::any visitColumn_specifications(DapParser::Column_specificationsContext *context) = 0;

    virtual std::any visitMeans_main(DapParser::Means_mainContext *context) = 0;

    virtual std::any visitMeans_proc(DapParser::Means_procContext *context) = 0;

    virtual std::any visitRun_main(DapParser::Run_mainContext *context) = 0;

    virtual std::any visitRun_stmt(DapParser::Run_stmtContext *context) = 0;


};

