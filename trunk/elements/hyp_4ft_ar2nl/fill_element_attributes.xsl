<?xml version="1.0" encoding="windows-1250" ?>

<xsl:stylesheet 
      xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
      version="1.0">
          
	
	<xsl:key name="klic_cedenty" match="ti_cedent" use="@id" />
	
	
	<!-- nastaveni jazyka (defaultne cz) -->
	<xsl:variable name="lng">cz</xsl:variable>

  <xsl:variable name="label_sent_count">
    <xsl:choose>
      <!-- cesky -->

      <xsl:when test="$lng='cz'">
        <xsl:text>Nalezen�ch v�t</xsl:text>
      </xsl:when>


      <!-- english-->

      <xsl:when test="$lng='en'">
        <xsl:text>Sentences count</xsl:text>
      </xsl:when>
    </xsl:choose>
  </xsl:variable>

  <xsl:variable name="label_sentence">
    <xsl:choose>

      <!-- cesky -->

      <xsl:when test="$lng='cz'">
        <xsl:text>V�ta </xsl:text>
      </xsl:when>


      <!-- english-->

      <xsl:when test="$lng='en'">
        <xsl:text>Sentence </xsl:text>
      </xsl:when>

    </xsl:choose>
  </xsl:variable>
  <!-- end of: labely polozek-->



  <!-- hlavni sablona -->
	<xsl:template match="hyp_4ft_ar2nl">

    <xsl:element name="element_attributes">
      <xsl:apply-templates select="@*"/>
      
      <!--pocet nalezenych vet-->
      <xsl:variable name="sent_count" select="count(sentences/sentence)"/>
      <xsl:element name="attribute">
        <xsl:attribute name="name">sentences_count</xsl:attribute>
        <xsl:attribute name="value">
          <xsl:value-of select="$sent_count"/>
        </xsl:attribute>
        <xsl:attribute name="label">
          <xsl:value-of select="$label_sent_count"/>
        </xsl:attribute>
      </xsl:element>

      <!--Seznam vsech vet-->
      <xsl:for-each select="sentences/sentence">
        <!--poradi vety v seznamu-->
        <xsl:variable name="index" select="position()"/>
        
        <xsl:element name="attribute">
          <xsl:attribute name="name">
            <xsl:value-of select="'sentence_'"/>
            <xsl:value-of select="$index"/>
          </xsl:attribute>
          <xsl:attribute name="value">
            <xsl:value-of select="."/>
          </xsl:attribute>
          <xsl:attribute name="label">
            <xsl:value-of select="$label_sentence"/>
            <xsl:value-of select="$index"/>
          </xsl:attribute>
        </xsl:element>
      </xsl:for-each>
    </xsl:element>
				
	</xsl:template>

	
	
	
	
	<!-- vypise vsechny atributy -->
	<xsl:template match="@*">
		
		
			<!-- labely polozek-->
		<xsl:variable name="label">
			<xsl:choose>
			
				<!-- nezavisle na jazyce -->
				
				<xsl:when test="name()='conf'">
					<xsl:text>Confidence: a/(a+b)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='d_conf'">
					<xsl:text>D-Confidence: a/(a+b+c)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='e_conf'">
					<xsl:text>E-Confidence: (a+d)/(a+b+c+d)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='support'">
					<xsl:text>Support: a/(a+b+c+d)</xsl:text>
				</xsl:when>
						
				<xsl:when test="name()='completeness'">
					<xsl:text>Completeness: a/(a+c)</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='avg_diff'">
					<xsl:text>Average difference: a(a+b+c+d)/((a+b)(a+c))- 1</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_imp'">
					<xsl:text>Lower bound implication</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_imp'">
					<xsl:text>Upper bound implication</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_dbl_imp'">
					<xsl:text>Lower bound double implication</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_dbl_imp'">
					<xsl:text>Upper bound double implication</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='low_bnd_eq'">
					<xsl:text>Lower bound equivalence</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='up_bnd_eq'">
					<xsl:text>Upper bound equivalence</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='fisher'">
					<xsl:text>Fisher test</xsl:text>
				</xsl:when>
							
				<xsl:when test="name()='chi_sq'">
					<xsl:text>Chi-square test</xsl:text>
				</xsl:when>
				
				
				<!-- cesky -->
				
				<xsl:when test="$lng='cz'">    
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Datab�ze</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Datov� matice</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Jm�no �lohy</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>
				</xsl:when>
				
				
				<!-- english-->
				
				<xsl:when test="$lng='en'">	
						<xsl:choose>
							<xsl:when test="name()='db_name'">
								<xsl:text>Database</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='matrix_name'">
								<xsl:text>Data matrix</xsl:text>
							</xsl:when>
							
							<xsl:when test="name()='task_name'">
								<xsl:text>Task name</xsl:text>
							</xsl:when>
							
							<xsl:otherwise>
								<xsl:value-of select="name()"/>
							</xsl:otherwise>
						</xsl:choose>	
				</xsl:when>
				
				<!-- jinak se pouzije nazev XML atributu-->
				
				<xsl:otherwise>
					<xsl:value-of select="name()"/>
				</xsl:otherwise>
				
			</xsl:choose>
		</xsl:variable>
			<!-- end of: labely polozek-->
		
			
			
			
			<attribute name="{name()}" value="{.}" label="{$label}" />
				
	</xsl:template>
	<!-- vypise vsechny atributy -->





	<!-- naplni hodnotu cedentu-->
	<xsl:template match="@antecedent | @succedent | @condition">
	
					<!-- zapise: <attribute name="{name()}" value="-->

					<xsl:text disable-output-escaping="yes">
					&lt;attribute name="</xsl:text>

					<xsl:value-of select="name()"/>
					
					<xsl:text disable-output-escaping="yes">" value="</xsl:text>
		
		

					<!-- zapise hodnotu cedentu -->
					<xsl:apply-templates select="id(.)" mode="values"/>


					<xsl:text disable-output-escaping="yes">" /&gt;</xsl:text>

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
