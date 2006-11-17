<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne en) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">



    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- cesky -->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="task_name" label="Jméno úlohy" />
          </xsl:when>

          <!-- english-->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        <!-- nezavisle na jazyce -->
        <attribute name="a" label="a" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="b" label="b" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="c" label="c" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="d" label="d" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="e" label="e" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="f" label="f" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="g" label="g" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="h" label="h" numeric_sort="true" default_sort_direction="descending"/>
        
        <attribute name="conf1" label="Confidence 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="d_conf1" label="D-Confidence 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="e_conf1" label="E-Confidence 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="support1" label="Support 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="completeness1" label="Completeness 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="avg_diff1" label="Average difference 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_imp1" label="Lower bound implication 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_imp1" label="Upper bound implication 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_dbl_imp1" label="Upper bound implication 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_dbl_imp1" label="Upper bound double implication 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_eq1" label="Lower bound equivalence 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_eq1" label="Upper bound equivalence 1" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fisher1" label="Fisher test 1" numeric_sort="true" />
        <attribute name="chi_sq1" label="Chi-square test 1" numeric_sort="true" />

        <attribute name="conf2" label="Confidence 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="d_conf2" label="D-Confidence 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="e_conf2" label="E-Confidence 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="support2" label="Support 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="completeness2" label="Completeness 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="avg_diff2" label="Average difference 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_imp2" label="Lower bound implication 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_imp2" label="Upper bound implication 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_dbl_imp2" label="Upper bound implication 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_dbl_imp2" label="Upper bound double implication 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="low_bnd_eq2" label="Lower bound equivalence 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="up_bnd_eq2" label="Upper bound equivalence 2" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="fisher2" label="Fisher test 2" numeric_sort="true" />
        <attribute name="chi_sq2" label="Chi-square test 2" numeric_sort="true" />

        <attribute name="dr_sum" label="D%-Sum" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="df_conf" label="Df-Conf" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="df_dfui" label="Df-DFUI" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="df_fue" label="Df-FUE" numeric_sort="true" default_sort_direction="descending"/>
        <attribute name="df_avg" label="Df-Avg" numeric_sort="true" default_sort_direction="descending"/>
        
        <attribute name="antecedent" label="Antecedent" />
        <attribute name="succedent" label="Succedent"/>
        <attribute name="condition"  label="Condition"/>

        <xsl:choose>

          <!-- cesky -->
          <xsl:when test="$lng='cz'">
            <attribute name="set1"  label="První množina"/>
            <attribute name="set2"  label="Druhá množina"/>
          </xsl:when>

          <!-- english-->
          <xsl:when test="$lng='en'">
            <attribute name="set1"  label="First set"/>
            <attribute name="set2"  label="Second set"/>
          </xsl:when>
        </xsl:choose>
        
        
      </attributes>

      <values>
        <xsl:apply-templates select="hyp_sd4ft" mode="values"/>
      </values>

    </dialog_data>


  </xsl:template>




  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>



    
    
    
    <xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>

	
	
	<!-- naplni hodnotu cedentu-->
	<xsl:template match="@antecedent | @succedent | @condition | @set1 | @set2" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
    	<xsl:apply-templates select="id(.)" mode="values"/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

    	<xsl:apply-templates select="@*"/>
	</xsl:template>
	

	<!-- literaly -> cedent -->
	<xsl:template match="ti_cedent" mode="values">		
    	<xsl:apply-templates select="ti_literal" mode="values"/>
	</xsl:template>
	

	<!-- preformatuje literal -->
	<xsl:template match="ti_literal" mode="values">		
		
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no"> &amp; </xsl:text>
		</xsl:if>

		
		<xsl:value-of select="@quant"/>
		<xsl:text disable-output-escaping="yes">(</xsl:text>
		<xsl:value-of select="@value"/>
		<xsl:text disable-output-escaping="yes">)</xsl:text>
	</xsl:template>
	


</xsl:stylesheet>
