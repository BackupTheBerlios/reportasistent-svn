<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">

  <!-- nastaveni jazyka (defaultne cz) -->
  <xsl:variable name="lng">en</xsl:variable>


  <xsl:template match="/active_list">

    <dialog_data>
      <attributes>
        <attribute name="id" label="id" />

        <xsl:choose>

          <!-- english -->
          <xsl:when test="$lng='en'">
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
            <attribute name="task_type" label="Task type" />
            <attribute name="cedent_type" label="Cedent type" />
            <attribute name="sub_cedent_cnt" label="Count of sub-cedents" numeric_sort="true"/>
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="task_name" label="Jméno úlohy" />
            <attribute name="task_type" label="Typ úlohy" />
            <attribute name="cedent_type" label="Typ cedentu" />
            <attribute name="sub_cedent_cnt" label="Počet sub-cedentů" numeric_sort="true"/>
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

      </attributes>

      <values>
        <xsl:apply-templates select="KL_cedent" mode="values"/>
      </values>

    </dialog_data>

  </xsl:template>






  <!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>

		<!--<xsl:text disable-output-escaping="yes">structure="</xsl:text>
		<xsl:apply-templates select="sub_KL_cedent" mode="values"/>
		<xsl:text disable-output-escaping="yes">" </xsl:text>-->
		<!--
		<xsl:text disable-output-escaping="yes">missing_values="</xsl:text>
		<xsl:apply-templates select="missing_value" mode="values"/>
		<xsl:text disable-output-escaping="yes">"</xsl:text>
        -->
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	<!-- naplni hodnotu pro categories -->
	<xsl:template match="sub_KL_cedent" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>

		<xsl:text disable-output-escaping="no">(name: </xsl:text>
		<xsl:value-of select="@name"/>
		<xsl:text disable-output-escaping="no">; literal_cnt: </xsl:text>
		<xsl:value-of select="@literal_cnt"/>
		<xsl:text disable-output-escaping="no">; length: </xsl:text>
		<xsl:value-of select="@length"/>
		<xsl:text disable-output-escaping="no">; literals: {</xsl:text>
		
		<xsl:apply-templates select="KL_literal" mode="values"/>
		<xsl:text disable-output-escaping="no">}</xsl:text>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	
	<xsl:template match="KL_literal" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>
		
		<xsl:text disable-output-escaping="no">(underlying attribute: </xsl:text>
		<xsl:value-of select="@underlying_attribute"/>
		<xsl:text disable-output-escaping="no">; category_cnt: </xsl:text>
		<xsl:value-of select="@category_cnt"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	



</xsl:stylesheet>
