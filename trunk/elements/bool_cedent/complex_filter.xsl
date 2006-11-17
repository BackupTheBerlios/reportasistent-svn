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
            <attribute name="name" label="Name" />
            <attribute name="db_name" label="Database" />
            <attribute name="matrix_name" label="Data matrix" />
            <attribute name="task_name" label="Task name" />
            <attribute name="task_type" label="Task type" />
            <attribute name="cedent_type" label="Cedent type" />
            <attribute name="literal_cnt" label="Count of literals" />
            <attribute name="length" label="Length" />
          </xsl:when>

          <!-- cesky-->
          <xsl:when test="$lng='cz'">
            <attribute name="name" label="Název" />
            <attribute name="db_name" label="Databáze" />
            <attribute name="matrix_name" label="Datová matice" />
            <attribute name="task_name" label="Jméno úlohy" />
            <attribute name="task_type" label="Typ úlohy" />
            <attribute name="cedent_type" label="Typ cedentu" />
            <attribute name="literal_cnt" label="Počet literálů" />
            <attribute name="length" label="Délka" />
          </xsl:when>
        </xsl:choose>

        <!-- vychozi hodnoty:
                numeric_sort="false"
                default_sort_direction="ascending"     -->

        </attributes>

      <values>
        <xsl:apply-templates select="bool_cedent" mode="values"/>
      </values>

    </dialog_data>

    

  </xsl:template>
	





	<!-- vypise hodnoty -->
	<xsl:template match="node()" mode="values">		
		

		<xsl:text disable-output-escaping="yes">
		&lt;value </xsl:text>
		<xsl:apply-templates select="@*" mode="values"/>
		<!-- vypsani literalu--><!--
		<xsl:text disable-output-escaping="yes">literals="</xsl:text>
		<xsl:apply-templates select="literal" mode="values" />-->
		<xsl:text disable-output-escaping="yes">/&gt;</xsl:text>


	</xsl:template>



	



	
	<!--<xsl:template match="literal" mode="values">
		<xsl:if test="position()!=1">
			<xsl:text disable-output-escaping="no">; </xsl:text>
		</xsl:if>
		
		<xsl:text disable-output-escaping="no">(underlying attribute: </xsl:text>
		<xsl:value-of select="@underlying_attribute"/>
		<xsl:text disable-output-escaping="no">; category count: </xsl:text>
		<xsl:value-of select="@category_cnt"/>
		<xsl:text disable-output-escaping="no">; missing type: </xsl:text>
		<xsl:value-of select="@missing_type"/>
		<xsl:text disable-output-escaping="no">; coefficient type: </xsl:text>
		<xsl:value-of select="@coefficient_type"/>
		<xsl:text disable-output-escaping="no">; length: </xsl:text>
		<xsl:value-of select="@length"/>
		<xsl:text disable-output-escaping="no">; gace: </xsl:text>
		<xsl:value-of select="@gace"/>
		<xsl:text disable-output-escaping="no">; literal type: </xsl:text>
		<xsl:value-of select="@literal_type"/>
		<xsl:text disable-output-escaping="no">; equivalence class: </xsl:text>
		<xsl:value-of select="@equivalence_class"/>
		<xsl:text disable-output-escaping="no">)</xsl:text>
	</xsl:template>-->



	<!-- naplni hodnotu -->
	<xsl:template match="@*" mode="values">
	
		<xsl:value-of select="name()"/>
		
		<xsl:text disable-output-escaping="yes">="</xsl:text>
	
		<xsl:value-of select="."/>

		<xsl:text disable-output-escaping="yes">" </xsl:text>

	</xsl:template>

	
	



</xsl:stylesheet>
